#include "deck_modifier.h"

#include "card.h"
#include "constants.h"
#include "deck_state_impl.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <random>
#include <stdexcept>
#include <vector>

namespace
{
bool ValuesMatch(const Card player_card, const DeckState::CardSet& cards_to_take)
{
    return true;
}

void ReturnCards(DeckState::CardSet& talon, DeckState::CardSet&& cards_to_return)
{
    talon.insert(cards_to_return.begin(), cards_to_return.end());
}

/**
 * Picks n_cards at random from source and returns them as a set. The same cards are removed from
 * the source.
 */
DeckState::CardSet PickAtRandom(DeckState::CardSet& source, std::uint32_t n_cards)
{
    if (source.size() < n_cards)
    {
        throw std::invalid_argument("Source does not contain enough cards.");
    }

    std::vector<Card> card_vec;
    card_vec.reserve(source.size());
    std::copy(source.begin(), source.end(), std::back_inserter(card_vec));
    assert(card_vec.size() == source.size());

    static std::mt19937 random_engine{};
    DeckState::CardSet picked_cards{};

    for (std::uint32_t i = 0; i < n_cards; ++i)
    {
        const auto max_index = card_vec.size() - i - 1;
        std::uniform_int_distribution<std::size_t> dist(0, max_index);
        auto random_index = dist(random_engine);
        picked_cards.insert(card_vec.at(random_index));
        source.erase(card_vec[random_index]);
        card_vec[random_index] = card_vec.at(max_index);
    }

    return picked_cards;
}

}  // namespace

MoveStatus DeckModifier::MakeMove(DeckState& deck_state,
                                  std::uint32_t player_idx,
                                  Card player_card,
                                  std::unordered_set<Card> cards_to_take)
{
    if (player_idx >= kMaxPlayers)
    {
        return MoveStatus::kInvalidPlayerIndex;
    }

    assert(deck_state.impl_);
    auto& deck_state_impl = *deck_state.impl_;

    auto& player_cards = deck_state_impl.player_hand_.at(player_idx);
    auto card_to_play = std::find(player_cards.begin(), player_cards.end(), player_card);
    if (card_to_play == player_cards.end())
    {
        return MoveStatus::kUnavailablePlayerCard;
    }

    auto& talon = deck_state_impl.talon_;
    std::unordered_set<Card> taken_cards{};
    for (const auto card : cards_to_take)
    {
        if (talon.erase(card) == 0)
        {
            talon.insert(taken_cards.begin(), taken_cards.end());
            return MoveStatus::kUnavailableTalonCard;
        }
        taken_cards.insert(card);
    }

    if (!ValuesMatch(player_card, taken_cards))
    {
        talon.insert(taken_cards.begin(), taken_cards.end());
        return MoveStatus::kValueMismatch;
    }

    auto& player_taken = deck_state_impl.player_taken_.at(player_idx);
    player_cards.erase(player_card);
    player_taken.insert(player_card);
    player_taken.insert(taken_cards.begin(), taken_cards.end());

    return MoveStatus::kOk;
}

DealStatus DeckModifier::DealCards(
    DeckState::Impl& deck_state_impl,
    std::uint32_t player_idx,
    std::function<typename DeckState::CardSet(typename DeckState::CardSet& source)> card_picker)
{
    if (player_idx >= kMaxPlayers)
    {
        return DealStatus::kInvalidPlayerIndex;
    }

    auto& player_hand = deck_state_impl.player_hand_.at(player_idx);
    if (!player_hand.empty())
    {
        return DealStatus::kPlayerNotEmpty;
    }

    auto& stock = deck_state_impl.stock_;
    if (stock.size() < kNCardsInHand)
    {
        return DealStatus::kUnavailableStockCard;
    }

    player_hand = card_picker ? card_picker(stock) : PickAtRandom(stock, kNCardsInHand);

    return DealStatus::kOk;
}

#include "make_move.h"

#include "constants.h"
#include "deck_state.h"
#include "deck_state_impl.h"

#include <algorithm>
#include <cassert>

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

}  // namespace

MoveStatus MakeMove(DeckState& deck_state,
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

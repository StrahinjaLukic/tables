#include "deck_state_impl.h"

#include <cassert>

namespace
{
static const std::unordered_set<Rank> kRanks = {Rank::kA,
                                                Rank::k2,
                                                Rank::k3,
                                                Rank::k4,
                                                Rank::k5,
                                                Rank::k6,
                                                Rank::k7,
                                                Rank::k8,
                                                Rank::k9,
                                                Rank::k10,
                                                Rank::kJ,
                                                Rank::kQ,
                                                Rank::kK};

static const std::unordered_set<Suit> kSuits = {
    Suit::kClubs, Suit::kDiamonds, Suit::kHearts, Suit::kSpades};

DeckState::CardSet MakeFullDeck()
{
    DeckState::CardSet card_set;
    for (const auto suit : kSuits)
    {
        for (const auto rank : kRanks)
        {
            const auto e = card_set.emplace(suit, rank);
            assert(e.second);
        }
    }
    return card_set;
}

}  // namespace

DeckState::Impl::Impl() : stock_(MakeFullDeck()) {}

DeckState::CardSet DeckState::Impl::PlayerHand(std::uint32_t player_idx)
{
    return player_hand_.at(player_idx);
}

DeckState::CardSet DeckState::Impl::PlayerTaken(std::uint32_t player_idx)
{
    return player_taken_.at(player_idx);
}

DeckState::CardSet DeckState::Impl::Talon()
{
    return talon_;
}

DeckState::CardSet DeckState::Impl::Stock()
{
    return stock_;
}

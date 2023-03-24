#include "make_full_deck.h"

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

using CardSet = std::unordered_set<Card>;

}  // namespace

CardSet MakeFullDeck()
{
    CardSet card_set;
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
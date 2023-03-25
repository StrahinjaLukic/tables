#include "card.h"
#include "constants.h"
#include "deck_state.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>

namespace
{
using testing::Contains;
using testing::IsEmpty;

MATCHER_P(SuitMatches, suit, "")
{
    return arg.GetSuit() == suit;
};
}  // namespace

TEST(DealTest, RegularStartingDeal)
{
    const auto deck_state = DeckState::StartingDeck();
    const auto& stock = deck_state.Stock();
    EXPECT_THAT(stock, Contains(SuitMatches(Suit::kClubs)).Times(13));
    EXPECT_THAT(stock, Contains(SuitMatches(Suit::kDiamonds)).Times(13));
    EXPECT_THAT(stock, Contains(SuitMatches(Suit::kHearts)).Times(13));
    EXPECT_THAT(stock, Contains(SuitMatches(Suit::kSpades)).Times(13));
    for (int iPlayer = 0; iPlayer < kMaxPlayers; ++iPlayer)
    {
        EXPECT_THAT(deck_state.PlayerHand(iPlayer), IsEmpty());
        EXPECT_THAT(deck_state.PlayerTaken(iPlayer), IsEmpty());
    }
    EXPECT_THAT(deck_state.Talon(), IsEmpty());
}
#include "card.h"
#include "constants.h"
#include "deal.h"
#include "deck_state.h"
#include "enum/deal_status.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>

namespace
{

using testing::Contains;
using testing::IsEmpty;
using testing::Values;

MATCHER_P(SuitMatches, suit, "")
{
    return arg.GetSuit() == suit;
};

class DealTest : public testing::TestWithParam<int>
{
};

}  // namespace

TEST(DealTest, RegularStartingDeck)
{
    const auto deck_state = DeckState::StartingDeck(2);
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

TEST_P(DealTest, DealFirstHand)
{
    auto deck_state = DeckState::StartingDeck(GetParam());
    EXPECT_EQ(DealStatus::kOk, Deal(deck_state));
}

INSTANTIATE_TEST_SUITE_P(DealFirstHandCases, DealTest, Values(2, 4));

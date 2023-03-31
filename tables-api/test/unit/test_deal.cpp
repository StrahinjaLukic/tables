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
    EXPECT_THAT(stock, Contains(SuitMatches(Suit::kClubs)).Times(kNRanks));
    EXPECT_THAT(stock, Contains(SuitMatches(Suit::kDiamonds)).Times(kNRanks));
    EXPECT_THAT(stock, Contains(SuitMatches(Suit::kHearts)).Times(kNRanks));
    EXPECT_THAT(stock, Contains(SuitMatches(Suit::kSpades)).Times(kNRanks));
    for (int iPlayer = 0; iPlayer < kMaxPlayers; ++iPlayer)
    {
        EXPECT_THAT(deck_state.PlayerHand(iPlayer), IsEmpty());
        EXPECT_THAT(deck_state.PlayerTaken(iPlayer), IsEmpty());
    }
    EXPECT_THAT(deck_state.Talon(), IsEmpty());
}

TEST_P(DealTest, DealFirstHand)
{
    const auto& n_players = GetParam();

    auto deck_state = DeckState::StartingDeck(n_players);

    EXPECT_EQ(DealStatus::kOk, Deal(deck_state));
    const auto& stock = deck_state.Stock();

    EXPECT_EQ(stock.size(), kDeckSize - n_players * kNCardsInHand);
    for (int iPlayer = 0; iPlayer < n_players; ++iPlayer)
    {
        EXPECT_EQ(kNCardsInHand, deck_state.PlayerHand(iPlayer).size());
        EXPECT_THAT(deck_state.PlayerTaken(iPlayer), IsEmpty());
    }
    EXPECT_THAT(deck_state.Talon(), IsEmpty());
}

INSTANTIATE_TEST_SUITE_P(DealFirstHandCases, DealTest, Values(2, 4));

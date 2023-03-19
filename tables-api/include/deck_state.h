#pragma once

#include "card.h"

#include <memory>
#include <unordered_set>

enum class MoveStatus;

/**
 * Class [DeckState] stores the state of the card deck at the given point in the game.
 * The state of the deck is described by defining the sets of the cards at all relevant locations at
 * the table: Cards held in each players hands, cards taken by each player, the talon, and the
 * remaining cards to deal.
 */
class DeckState
{
public:
    using CardSet = std::unordered_set<Card>;

    DeckState();
    ~DeckState();

    /** Returns the set of cards held by the player with index player_idx in their hands. */
    CardSet PlayerHand(std::uint32_t player_idx);
    /** Returns the set of cards taken by the player with index player_idx. */
    CardSet PlayerTaken(std::uint32_t player_idx);
    /** Returns the set of cards laid down facing up on the table (the "talon"). */
    CardSet Talon();
    /** Returns the set of cards remaining to be dealt in the forthcoming rounds. */
    CardSet Remaining();

private:
    friend MoveStatus MakeMove(DeckState& deck_state,
                               std::uint32_t player_idx,
                               Card player_card,
                               std::unordered_set<Card> cards_to_take);
    class Impl;
    std::unique_ptr<Impl> impl_;
};

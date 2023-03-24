#pragma once

#include "card.h"
#include "constants.h"

#include <array>
#include <memory>
#include <unordered_set>

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

    ~DeckState();

    DeckState(DeckState&& other);

    /** Returns the set of cards held by the player with index player_idx in their hands. */
    CardSet PlayerHand(std::uint32_t player_idx);
    /** Returns the set of cards taken by the player with index player_idx. */
    CardSet PlayerTaken(std::uint32_t player_idx);
    /** Returns the set of cards laid down facing up on the table (the "talon"). */
    CardSet Talon();
    /** Returns the set of cards remaining to be dealt in the forthcoming rounds. */
    CardSet Stock();

    /**
     * Returns the deck state as described by the arguments.
     *
     * @param player_hands array of player hands
     * @param player_takens array of card sets representing cards taken by each player.
     * @param talon
     * @param stock
     *
     * @note The validity of the requested deck state is not checked. Subsequent operations on the
     * deck may return errors if the state is inconsistent.
     */
    static DeckState SetUpDeck(std::array<CardSet, kMaxPlayers> player_hands,
                               std::array<CardSet, kMaxPlayers> player_takens,
                               CardSet talon,
                               CardSet stock);

    /**
     * Returns the deck state at the beginning of a game.
     */
    static DeckState StartingDeck();

private:
    friend class DeckModifier;

    DeckState();

    class Impl;
    std::unique_ptr<Impl> impl_;
};

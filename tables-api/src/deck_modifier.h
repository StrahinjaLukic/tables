#pragma once

#include "card.h"
#include "deck_state.h"
#include "enum/deal_status.h"
#include "enum/move_status.h"

#include <cstdint>
#include <unordered_set>

class DeckState;

/** Encapsulates operations on the card deck. */
class DeckModifier
{
public:
    static MoveStatus MakeMove(DeckState& deck_state,
                               std::uint32_t player_idx,
                               Card player_card,
                               std::unordered_set<Card> cards_to_take);
    /**
     * Deal a hand of cards to a single player.
     *
     * @param deck_state [DeckState] of the game.
     * @param player_idx Index of the player who should receive the cards.
     *
     * @return [DealStatus] Indicate a successful deal ([kOk]) or an error.
     *
     * @note If the returned status is different than [DealStatus::kOk], the deal could not be made
     * and the deck state is not changed.
     */
    static DealStatus DealCards(DeckState::Impl& deck_state_impl, std::uint32_t player_idx);
};
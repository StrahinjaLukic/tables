#pragma once

#include "card.h"
#include "deck_state.h"
#include "enum/deal_status.h"
#include "enum/move_status.h"

#include <cstdint>
#include <functional>
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
     * Deal a round of cards to all players in the game.
     *
     * @param deck_state [DeckState] of the game.
     * @param card_picker Optional functor to use for picking cards from the stock. If not provided
     * (default), cards will be randomly selected.
     *
     * @return [DealStatus] Indicate a successful deal ([kOk]) or an error.
     *
     * @note If the returned status is different than [DealStatus::kOk], the deal could not be made
     * and the deck state is not changed.
     */
    static DealStatus DealCards(
        DeckState& deck_state,
        std::function<typename DeckState::CardSet(typename DeckState::CardSet& source)>
            card_picker = nullptr);
};
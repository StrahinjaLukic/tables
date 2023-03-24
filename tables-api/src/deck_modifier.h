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
     * Deal a random hand of cards from the stock to a single player.
     *
     * @param deck_state [DeckState] of the game.
     * @param player_idx Index of the player who should receive the cards.
     * @param card_picker Optional functor to use for picking cards from the stock. If not provided
     * (default), cards will be randomly selected.
     *
     * @return [DealStatus] Indicate a successful deal ([kOk]) or an error.
     *
     * @note If the returned status is different than [DealStatus::kOk], the deal could not be made
     * and the deck state is not changed.
     */
    static DealStatus DealCards(
        DeckState::Impl& deck_state_impl,
        std::uint32_t player_idx,
        std::function<typename DeckState::CardSet(typename DeckState::CardSet& source)>
            card_picker = nullptr);
};
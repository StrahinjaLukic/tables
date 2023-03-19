#pragma once

#include "card.h"
#include "enum/move_status.h"

#include <cstdint>
#include <unordered_set>

class DeckState;

/**
 * Perform a move in the game.
 *
 * @param deck_state [DeckState] of the game.
 * @param player_idx index of the player who is making the move.
 * @param player_card Card that the player is playing.
 * @param taken_cards Cards that the player is taking, if any.
 *
 * @return [MoveStatus] Indicate a successful move ([kOk]) or an error.
 *
 * @note If the returned status is different than [MoveStatus::kOk], the move could not be made and
 * the deck state is not changed.
 */
MoveStatus MakeMove(DeckState& deck_state,
                    std::uint32_t player_idx,
                    Card player_card,
                    std::unordered_set<Card> cards_to_take);

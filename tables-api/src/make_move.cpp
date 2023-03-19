#include "make_move.h"

#include "deck_modifier.h"

MoveStatus MakeMove(DeckState& deck_state,
                    std::uint32_t player_idx,
                    Card player_card,
                    std::unordered_set<Card> cards_to_take)
{
    return DeckModifier::MakeMove(deck_state, player_idx, player_card, cards_to_take);
}

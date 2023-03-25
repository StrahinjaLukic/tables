#include "deal.h"

#include "deck_modifier.h"

DealStatus Deal(DeckState& deck_state)
{
    return DeckModifier::DealCards(deck_state);
}

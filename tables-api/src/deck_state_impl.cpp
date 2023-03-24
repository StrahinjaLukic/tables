#include "deck_state_impl.h"

#include "util/make_full_deck.h"

DeckState::Impl::Impl() : stock_(MakeFullDeck()) {}

DeckState::CardSet DeckState::Impl::PlayerHand(std::uint32_t player_idx)
{
    return player_hand_.at(player_idx);
}

DeckState::CardSet DeckState::Impl::PlayerTaken(std::uint32_t player_idx)
{
    return player_taken_.at(player_idx);
}

DeckState::CardSet DeckState::Impl::Talon()
{
    return talon_;
}

DeckState::CardSet DeckState::Impl::Stock()
{
    return stock_;
}

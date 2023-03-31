#include "deck_state_impl.h"

#include "util/make_full_deck.h"

DeckState::Impl::Impl() : stock_(MakeFullDeck()) {}

const DeckState::CardSet& DeckState::Impl::PlayerHand(std::uint32_t player_idx)
{
    return player_hand_.at(player_idx);
}

const DeckState::CardSet& DeckState::Impl::PlayerTaken(std::uint32_t player_idx)
{
    return player_taken_.at(player_idx);
}

const DeckState::CardSet& DeckState::Impl::Talon()
{
    return talon_;
}

const DeckState::CardSet& DeckState::Impl::Stock()
{
    return stock_;
}

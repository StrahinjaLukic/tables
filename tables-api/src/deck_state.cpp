#include "deck_state.h"

#include "deck_state_impl.h"

DeckState::DeckState() : impl_(std::make_unique<Impl>()) {}

DeckState::~DeckState() {}

DeckState::CardSet DeckState::PlayerHand(std::uint32_t player_idx)
{
    return impl_->PlayerHand(player_idx);
}

DeckState::CardSet DeckState::PlayerTaken(std::uint32_t player_idx)
{
    return impl_->PlayerTaken(player_idx);
}

DeckState::CardSet DeckState::Talon()
{
    return impl_->Talon();
}

DeckState::CardSet DeckState::Stock()
{
    return impl_->Stock();
}

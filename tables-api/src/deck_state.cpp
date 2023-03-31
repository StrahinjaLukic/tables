#include "deck_state.h"

#include "deck_state_impl.h"
#include "util/make_full_deck.h"

#include <utility>

DeckState::DeckState() : impl_(std::make_unique<Impl>()) {}

DeckState::~DeckState() {}

const DeckState::CardSet& DeckState::PlayerHand(std::uint32_t player_idx) const
{
    return impl_->PlayerHand(player_idx);
}

const DeckState::CardSet& DeckState::PlayerTaken(std::uint32_t player_idx) const
{
    return impl_->PlayerTaken(player_idx);
}

const DeckState::CardSet& DeckState::Talon() const
{
    return impl_->Talon();
}

const DeckState::CardSet& DeckState::Stock() const
{
    return impl_->Stock();
}

DeckState DeckState::SetUpDeck(std::array<CardSet, kMaxPlayers> player_hands,
                               std::array<CardSet, kMaxPlayers> player_takens,
                               CardSet talon,
                               CardSet stock,
                               int n_players)
{
    DeckState deck_state;
    deck_state.impl_->player_hand_ = std::move(player_hands);
    deck_state.impl_->player_taken_ = std::move(player_takens);
    deck_state.impl_->talon_ = std::move(talon);
    deck_state.impl_->stock_ = std::move(stock);
    deck_state.impl_->n_players_ = n_players;
    return deck_state;
}

DeckState DeckState::StartingDeck(int n_players)
{
    return SetUpDeck(std::array<CardSet, kMaxPlayers>{},
                     std::array<CardSet, kMaxPlayers>{},
                     {},
                     MakeFullDeck(),
                     n_players);
}

DeckState::DeckState(DeckState&& other) : impl_(std::move(other.impl_)) {}

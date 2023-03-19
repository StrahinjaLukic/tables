#pragma once

#include "constants.h"
#include "deck_state.h"

enum class MoveStatus;

class DeckState::Impl
{
public:
    Impl();

    CardSet PlayerHand(std::uint32_t player_idx);
    CardSet PlayerTaken(std::uint32_t player_idx);
    CardSet Talon();
    CardSet Stock();

private:
    friend class DeckModifier;

    std::array<CardSet, kMaxPlayers> player_hand_{CardSet{}, CardSet{}, CardSet{}, CardSet{}};
    std::array<CardSet, kMaxPlayers> player_taken_{CardSet{}, CardSet{}, CardSet{}, CardSet{}};
    CardSet talon_{};
    CardSet stock_;
};

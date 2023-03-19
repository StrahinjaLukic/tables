#include "deck_state.h"

#include <array>
#include <cassert>

namespace
{
static const std::unordered_set<Rank> kRanks = {Rank::kA,
                                                Rank::k2,
                                                Rank::k3,
                                                Rank::k4,
                                                Rank::k5,
                                                Rank::k6,
                                                Rank::k7,
                                                Rank::k8,
                                                Rank::k9,
                                                Rank::k10,
                                                Rank::kJ,
                                                Rank::kQ,
                                                Rank::kK};

static const std::unordered_set<Suit> kSuits = {
    Suit::kClubs, Suit::kDiamonds, Suit::kHearts, Suit::kSpades};

DeckState::CardSet MakeFullDeck()
{
    DeckState::CardSet card_set;
    for (const auto suit : kSuits)
    {
        for (const auto rank : kRanks)
        {
            const auto e = card_set.emplace(suit, rank);
            assert(e.second);
        }
    }
    return card_set;
}

}  // namespace

class DeckState::Impl
{
public:
    static constexpr auto kMaxPlayers = 4;

    Impl();

    CardSet PlayerHand(std::uint32_t player_idx);
    CardSet PlayerTaken(std::uint32_t player_idx);
    CardSet Talon();
    CardSet Remaining();

private:
    std::array<CardSet, kMaxPlayers> player_hand_{CardSet{}, CardSet{}, CardSet{}, CardSet{}};
    std::array<CardSet, kMaxPlayers> player_taken_{CardSet{}, CardSet{}, CardSet{}, CardSet{}};
    CardSet talon_{};
    CardSet remaining_;
};

DeckState::Impl::Impl() : remaining_(MakeFullDeck()) {}

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

DeckState::CardSet DeckState::Impl::Remaining()
{
    return remaining_;
}

/** Deck state */

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

DeckState::CardSet DeckState::Remaining()
{
    return impl_->Remaining();
}

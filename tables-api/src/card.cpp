#include "card.h"

#include <cstdint>

namespace
{
/** Maps individual cards to numbers for the purpose of hashing.*/
std::uint8_t Order(const Card& card)
{
    return (static_cast<std::uint8_t>(card.GetSuit()) << 4) + static_cast<int>(card.GetRank());
}
}  // namespace

Rank Card::GetRank() const
{
    return rank_;
}

Suit Card::GetSuit() const
{
    return suit_;
}

bool operator==(const Card& lhs, const Card& rhs)
{
    return lhs.GetSuit() == rhs.GetSuit() && lhs.GetRank() == rhs.GetRank();
}

std::size_t std::hash<Card>::operator()(const Card& card) const noexcept
{
    return std::hash<std::uint8_t>{}(Order(card));
}

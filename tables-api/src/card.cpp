#include "card.h"

#include <cstdint>

namespace
{
/** Maps individual cards to numbers for the purpose of hashing.*/
std::uint8_t Order(const Card& card)
{
    return (static_cast<std::uint8_t>(card.suit) << 4) + static_cast<int>(card.rank);
}
}  // namespace

bool operator==(const Card& lhs, const Card& rhs)
{
    return lhs.suit == rhs.suit && lhs.rank == rhs.rank;
}

std::size_t std::hash<Card>::operator()(const Card& card) const noexcept
{
    return std::hash<std::uint8_t>{}(Order(card));
}

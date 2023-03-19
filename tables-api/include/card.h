#pragma once

#include "enum/rank.h"
#include "enum/suit.h"

#include <functional>

struct Card
{
    const Suit suit;
    const Rank rank;
};

bool operator==(const Card& lhs, const Card& rhs);

template <>
struct std::hash<Card>
{
    std::size_t operator()(const Card& card) const noexcept;
};

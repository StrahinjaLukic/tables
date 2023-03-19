#pragma once

#include "enum/rank.h"
#include "enum/suit.h"

#include <functional>

class Card
{
public:
    Card(Suit suit, Rank rank);

    Suit GetSuit() const;
    Rank GetRank() const;

private:
    Suit suit_;
    Rank rank_;
};

bool operator==(const Card& lhs, const Card& rhs);

template <>
struct std::hash<Card>
{
    std::size_t operator()(const Card& card) const noexcept;
};

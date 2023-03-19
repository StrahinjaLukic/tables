#pragma once

enum class MoveStatus
{
    kOk,
    kInvalidPlayerIndex,
    kUnavailablePlayerCard,
    kUnavailableTalonCard,
    kValueMismatch
};

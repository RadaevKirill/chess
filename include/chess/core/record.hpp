#pragma once 

#include <optional>

#include "chess/core/move.hpp"

namespace chess::core {
    struct Record
    {
        Move move;
        std::optional<Move> captured_piece;

        bool previousCastlingRights;
        std::
    };
}
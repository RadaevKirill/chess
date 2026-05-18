#pragma once

#include <optional>

#include "chess/core/piece.hpp"
#include "chess/core/square.hpp"

namespace chess::core {

    struct Move {
        Square from;
        Square to;
        std::optional<Piece> promotion;
    };

}

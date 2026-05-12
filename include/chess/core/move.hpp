#pragma once

#include <optional>

#include "chess/core/piece.hpp"
#include "chess/core/square.hpp"

namespace chess::core {

struct Move {
    Square from;
    Square to;
    std::optional<PieceType> promotion;
};

[[nodiscard]] constexpr bool operator==(Move lhs, Move rhs) {
    return lhs.from == rhs.from && lhs.to == rhs.to && lhs.promotion == rhs.promotion;
}

}

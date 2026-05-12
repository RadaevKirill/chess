#pragma once

#include <array>
#include <optional>

#include "chess/core/board.hpp"
#include "chess/core/color.hpp"


namespace chess::core {

    struct State
    {
        Board board;
        Color side_to_move;

    };
}
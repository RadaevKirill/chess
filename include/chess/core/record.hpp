#pragma once 

#include <optional>

#include "chess/core/move.hpp"
#include "chess/core/piece.hpp"

namespace chess::core {
    struct Record
    {
        Move move;
        std::optional<Piece> captured_piece;

        bool previous_castling_rights;
    };
}
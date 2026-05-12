#pragma once

#include "chess/core/color.hpp"

namespace chess::core {

enum class PieceType {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn
};

struct Piece {
    Color color;
    PieceType type;
};

}

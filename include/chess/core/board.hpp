#pragma once

#include <array>
#include <optional>

#include "chess/core/piece.hpp"

namespace chess::core {

    class Board {
    public:
        Board();

        void initialize();
        void clear();

        /* 
            file is vertical (a, b, c, d, e, f, g, h), rank is horizontal (1, 2, 3, 4, 5, 6, 7, 8)
            for simple access, we can use 0-based indexing for both file and rank, where:
            file: 0 -> a, 1 -> b, etc.
        */
        [[nodiscard]] bool empty(int file, int rank) const;
        [[nodiscard]] std::optional<Piece> piece_at(int file, int rank) const;

        void set_piece(int file, int rank, Piece piece);
        void remove_piece(int file, int rank);

    private:
        std::array<std::array<std::optional<Piece>, 8>, 8> squares_;
    
    };
}
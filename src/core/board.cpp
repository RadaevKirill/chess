#include "chess/core/board.hpp"


namespace chess::core {
    Board::Board() {
        clear();
        initialize();
    }

    void Board::clear() {
        for (auto& rank : squares_) {
            for (auto& square : rank) {
                square.reset();
            }
        }
    }

    void Board::set_piece(int file, int rank, Piece piece) {
        squares_[rank][file] = piece;
    }

    void Board::remove_piece(int file, int rank) {
        squares_[rank][file].reset();
    }

    bool Board::empty(int file, int rank) const {
        return !squares_[rank][file].has_value();
    }

    std::optional<Piece> Board::piece_at(int file, int rank) const {
        return squares_[rank][file];
    }

    void Board::initialize() {
        // Place pawns
        for (int file = 0; file < 8; ++file) {
            squares_[1][file] = Piece{Color::White, PieceType::Pawn};
            squares_[6][file] = Piece{Color::Black, PieceType::Pawn};
        }

        // Place rooks
        squares_[0][0] = squares_[0][7] = Piece{Color::White, PieceType::Rook};
        squares_[7][0] = squares_[7][7] = Piece{Color::Black, PieceType::Rook};

        // Place knights
        squares_[0][1] = squares_[0][6] = Piece{Color::White, PieceType::Knight};
        squares_[7][1] = squares_[7][6] = Piece{Color::Black, PieceType::Knight};

        // Place bishops
        squares_[0][2] = squares_[0][5] = Piece{Color::White, PieceType::Bishop};
        squares_[7][2] = squares_[7][5] = Piece{Color::Black, PieceType::Bishop};

        // Place queens
        squares_[0][3] = Piece{Color::White, PieceType::Queen};
        squares_[7][3] = Piece{Color::Black, PieceType::Queen};

        // Place kings
        squares_[0][4] = Piece{Color::White, PieceType::King};
        squares_[7][4] = Piece{Color::Black, PieceType::King};
    }
}
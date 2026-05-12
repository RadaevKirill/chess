
#include "chess/core/game.hpp"

namespace chess::core {

    Game::Game() : state_{Board{}, Color::White} {}

    const State& Game::state() const {
        return state_;
    }

    bool Game::make_move(const Move& move) {
        if (!is_legal_move(move)) {
            return false;
        }

        const auto moving_piece = state_.board.piece_at(move.from.file, move.from.rank);
        const auto captured_piece = state_.board.piece_at(move.to.file, move.to.rank);

        history_.add_record(Record{move, captured_piece, false});

        state_.board.remove_piece(move.from.file, move.from.rank);
        state_.board.set_piece(move.to.file, move.to.rank, move.promotion.value_or(*moving_piece));
        state_.side_to_move = opposite(state_.side_to_move);

        return true;
    }

    bool Game::undo_move() {
        if (history_.history_count() == 0) {
            return false;
        }

        const Record record = history_.last_record();
        const auto moved_piece = state_.board.piece_at(record.move.to.file, record.move.to.rank);

        if (!moved_piece.has_value()) {
            return false;
        }

        state_.board.set_piece(record.move.from.file, record.move.from.rank, *moved_piece);

        if (record.captured_piece.has_value()) {
            state_.board.set_piece(record.move.to.file, record.move.to.rank, *record.captured_piece);
        } else {
            state_.board.remove_piece(record.move.to.file, record.move.to.rank);
        }

        history_.remove_last_record();
        state_.side_to_move = opposite(state_.side_to_move);

        return true;
    }

    bool Game::is_legal_move(const Move& move) const {
        if (!move.from.is_valid() || !move.to.is_valid()) {
            return false;
        }

        const auto moving_piece = state_.board.piece_at(move.from.file, move.from.rank);
        if (!moving_piece.has_value()) {
            return false;
        }

        if (moving_piece->color != state_.side_to_move) {
            return false;
        }

        const auto target_piece = state_.board.piece_at(move.to.file, move.to.rank);
        if (target_piece.has_value() && target_piece->color == moving_piece->color) {
            return false;
        }

        return true;
    }
}

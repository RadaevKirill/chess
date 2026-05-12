#include "chess/core/history.hpp"

#include <stdexcept>

namespace chess::core {

    void History::add_move(const Move& move) {
        if (move_count_ >= moves_.size()) {
            throw std::out_of_range("history is full");
        }

        moves_[move_count_] = move;
        ++move_count_;
    }

    void History::remove_last_move() {
        if (move_count_ == 0) {
            throw std::out_of_range("history is empty");
        }

        --move_count_;
    }

    const Move& History::get_move(size_t index) {
        if (index >= move_count_) {
            throw std::out_of_range("move index is out of range");
        }

        return moves_[index];
    }

    const Move& History::last_move() const {
        if (move_count_ == 0) {
            throw std::out_of_range("history is empty");
        }

        return moves_[move_count_ - 1];
    }

    size_t History::move_count() const {
        return move_count_;
    }

}

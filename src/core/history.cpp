#include "chess/core/history.hpp"

#include <stdexcept>

namespace chess::core {

    void History::add_record(const Record& record) {
        if (move_count_ >= moves_.size()) {
            throw std::out_of_range("history is full");
        }

        moves_[move_count_] = record;
        ++move_count_;
    }

    void History::remove_last_record() {
        if (move_count_ == 0) {
            throw std::out_of_range("history is empty");
        }

        --move_count_;
    }

    const Record& History::get_record(size_t index) {
        if (index >= move_count_) {
            throw std::out_of_range("record index is out of range");
        }

        return moves_[index];
    }

    const Record& History::last_record() const {
        if (move_count_ == 0) {
            throw std::out_of_range("history is empty");
        }

        return moves_[move_count_ - 1];
    }

    size_t History::history_count() const {
        return move_count_;
    }

}

#pragma once


#include "chess/core/state.hpp"
#include "chess/core/move.hpp"
#include "chess/core/history.hpp"

namespace chess::core {
    class Game {
        public:
            Game();

            const State& state() const;

            bool make_move(const Move& move);
            bool undo_move();

        private:
            State state_;
            History history_;

            bool is_legal_move(const Move& move) const;
    };
}
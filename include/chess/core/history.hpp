#pragma once

#include <array>
#include <cstddef>

#include "chess/core/move.hpp"

namespace chess::core {
    class History {
    public:
        void add_move(const Move& move);
        void remove_last_move();
        const Move& get_move(size_t index);

        [[nodiscard]] const Move& last_move() const;
        [[nodiscard]] size_t move_count() const;
    
    private:
        std::array<Move, 1024> moves_;
        size_t move_count_ = 0;
    };
}
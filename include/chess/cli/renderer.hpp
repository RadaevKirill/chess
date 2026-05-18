#pragma once

#include "chess/core/board.hpp"
#include "chess/core/move.hpp"
#include "chess/core/state.hpp"

#include <iosfwd>
#include <string_view>
#include <vector>

namespace chess::cli {
    class Renderer {
    public:
        explicit Renderer(std::ostream& output);

        void render_state(const core::State& state) const;
        void render_board(const core::Board& board) const;
        void render_moves(const std::vector<core::Move>& moves) const;
        void render_message(std::string_view message) const;
        void render_error(std::string_view message) const;
        void render_prompt() const;

    private:
        std::ostream& output_;
    };
}

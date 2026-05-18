#pragma once

#include "chess/cli/command.hpp"
#include "chess/cli/parser.hpp"
#include "chess/core/game.hpp"

#include <string>
#include <string_view>

namespace chess::cli {
    class Session {
    public:
        Session();

        [[nodiscard]] const core::Game& game() const;

        Command parse(std::string_view input) const;
        std::string handle(const Command& command);

    private:
        core::Game game_;
        CommandParser parser_;
    };
}

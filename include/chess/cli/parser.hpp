#pragma once

#include "chess/cli/command.hpp"

#include <string_view>
#include <string>

namespace chess::cli {

    class CommandParser {
    public:
        [[nodiscard]] Command parse(std::string_view input) const;
    };

}

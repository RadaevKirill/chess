#pragma once

#include <string>
#include <variant>

namespace chess::cli {

    struct HelpCommand {};
    struct ExitCommand {};
    struct BoardCommand {};
    struct MovesCommand {};
    struct UndoCommand {};
    struct ResetCommand {};
    struct ShowFenCommand {};

    struct MoveCommand {
        std::string move_text; // e2e4, g1f3, e7e8q
    };

    struct LoadFenCommand {
        std::string fen;
    };

    struct InvalidCommand {
        std::string message;
    };

    using Command = std::variant<
        HelpCommand,
        ExitCommand,
        BoardCommand,
        MovesCommand,
        UndoCommand,
        ResetCommand,
        ShowFenCommand,
        MoveCommand,
        LoadFenCommand,
        InvalidCommand
    >;

}

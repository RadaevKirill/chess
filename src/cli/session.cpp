#include "chess/cli/session.hpp"

#include "chess/core/color.hpp"
#include "chess/core/move.hpp"
#include "chess/core/piece.hpp"
#include "chess/core/square.hpp"

#include <optional>
#include <string>
#include <string_view>

namespace chess::cli {

Session::Session() = default;

// Даём доступ к игре только для чтения — const означает «не изменяй»
const core::Game& Session::game() const {
    return game_;
}

// Парсинг делегируем парсеру — Session сам ничего не разбирает
Command Session::parse(std::string_view input) const {
    return parser_.parse(input);
}

// Превращаем символ превращения ('q', 'r', 'b', 'n') в фигуру нужного цвета
static std::optional<core::Piece> parse_promotion(char ch, core::Color color) {
    using core::PieceType;
    switch (ch) {
        case 'q': return core::Piece{color, PieceType::Queen};
        case 'r': return core::Piece{color, PieceType::Rook};
        case 'b': return core::Piece{color, PieceType::Bishop};
        case 'n': return core::Piece{color, PieceType::Knight};
        default:  return std::nullopt;
    }
}

// Превращаем строку "e2e4" или "e7e8q" в структуру Move
static core::Move parse_move_text(std::string_view text, core::Color side_to_move) {
    // file: буква a-h → число 0-7
    const int from_file = text[0] - 'a';
    const int from_rank = text[1] - '1';
    const int to_file   = text[2] - 'a';
    const int to_rank   = text[3] - '1';

    std::optional<core::Piece> promotion;
    if (text.size() == 5) {
        promotion = parse_promotion(text[4], side_to_move);
    }

    return core::Move{
        core::Square{from_file, from_rank},
        core::Square{to_file,   to_rank},
        promotion
    };
}

// Обрабатываем команду и возвращаем строку-ответ для пользователя.
// std::visit — способ «заглянуть» внутрь variant и понять, что там лежит.
std::string Session::handle(const Command& command) {
    return std::visit([this](const auto& cmd) -> std::string {
        using T = std::decay_t<decltype(cmd)>;

        if constexpr (std::is_same_v<T, HelpCommand>) {
            return
                "Commands:\n"
                "  board      - show the board\n"
                "  moves      - list available moves (not implemented yet)\n"
                "  undo       - undo last move\n"
                "  reset      - restart the game\n"
                "  showfen    - show FEN string (not implemented yet)\n"
                "  loadfen X  - load position from FEN (not implemented yet)\n"
                "  e2e4       - make a move (from-square to-square)\n"
                "  exit/quit  - exit the program\n";

        } else if constexpr (std::is_same_v<T, ExitCommand>) {
            // Само завершение программы обрабатывает Repl
            return "";

        } else if constexpr (std::is_same_v<T, BoardCommand>) {
            // Ничего не возвращаем — Repl сам вызовет render_state
            return "";

        } else if constexpr (std::is_same_v<T, MovesCommand>) {
            return "Move generation is not implemented yet.";

        } else if constexpr (std::is_same_v<T, UndoCommand>) {
            if (game_.undo_move()) {
                return "Move undone.";
            }
            return "Nothing to undo.";

        } else if constexpr (std::is_same_v<T, ResetCommand>) {
            game_ = core::Game{};
            return "Game reset.";

        } else if constexpr (std::is_same_v<T, ShowFenCommand>) {
            return "FEN export is not implemented yet.";

        } else if constexpr (std::is_same_v<T, LoadFenCommand>) {
            return "FEN import is not implemented yet.";

        } else if constexpr (std::is_same_v<T, MoveCommand>) {
            const core::Move move = parse_move_text(cmd.move_text, game_.state().side_to_move);
            if (game_.make_move(move)) {
                return "OK";
            }
            return "Illegal move: " + cmd.move_text;

        } else if constexpr (std::is_same_v<T, InvalidCommand>) {
            return "Invalid command: " + cmd.message;
        }

        return "";
    }, command);
}

} // namespace chess::cli

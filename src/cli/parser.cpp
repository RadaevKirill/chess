#include "chess/cli/parser.hpp"

#include "chess/cli/command.hpp"

#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>

namespace chess::cli {

    namespace {

        [[nodiscard]] std::string_view trim(std::string_view text) {
            const auto is_space = [](unsigned char ch) {
                return std::isspace(ch) != 0;
            };

            while (!text.empty() && is_space(static_cast<unsigned char>(text.front()))) {
                text.remove_prefix(1);
            }

            while (!text.empty() && is_space(static_cast<unsigned char>(text.back()))) {
                text.remove_suffix(1);
            }

            return text;
        }

        [[nodiscard]] bool is_file(char ch) {
            return ch >= 'a' && ch <= 'h';
        }

        [[nodiscard]] bool is_rank(char ch) {
            return ch >= '1' && ch <= '8';
        }

        [[nodiscard]] bool is_promotion(char ch) {
            return ch == 'q' || ch == 'r' || ch == 'b' || ch == 'n';
        }

        [[nodiscard]] bool is_move_text(std::string_view text) {
            if (text.size() != 4 && text.size() != 5) {
                return false;
            }

            if (!is_file(text[0]) || !is_rank(text[1]) || !is_file(text[2]) || !is_rank(text[3])) {
                return false;
            }

            return text.size() == 4 || is_promotion(text[4]);
        }

    }

    Command CommandParser::parse(std::string_view input) const {
        const std::string_view text = trim(input);

        if (text.empty()) {
            return InvalidCommand{"empty command"};
        }

        if (text == "help") {
            return HelpCommand{};
        }

        if (text == "exit" || text == "quit") {
            return ExitCommand{};
        }

        if (text == "board") {
            return BoardCommand{};
        }

        if (text == "moves") {
            return MovesCommand{};
        }

        if (text == "undo") {
            return UndoCommand{};
        }

        if (text == "reset") {
            return ResetCommand{};
        }

        if (text == "showfen") {
            return ShowFenCommand{};
        }

        constexpr std::string_view load_fen_prefix = "loadfen";
        if (text.starts_with(load_fen_prefix)) {
            std::string_view fen = trim(text.substr(load_fen_prefix.size()));
            if (fen.empty()) {
                return InvalidCommand{"loadfen requires a FEN string"};
            }

            return LoadFenCommand{std::string{fen}};
        }

        std::string move_text{text};
        std::ranges::transform(move_text, move_text.begin(), [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        });

        if (is_move_text(move_text)) {
            return MoveCommand{std::move(move_text)};
        }

        return InvalidCommand{"unknown command"};
    }

}

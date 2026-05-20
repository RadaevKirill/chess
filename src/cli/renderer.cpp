#include "chess/cli/renderer.hpp"

#include "chess/core/color.hpp"
#include "chess/core/piece.hpp"

#include <ostream>
#include <string_view>

namespace chess::cli {

// Конструктор: сохраняем ссылку на поток вывода (например, std::cout)
Renderer::Renderer(std::ostream& output) : output_(output) {}

// Символ для шахматной фигуры в Unicode
// Белые фигуры — заполненные, чёрные — контурные
static char piece_char(const chess::core::Piece& piece) {
    using chess::core::Color;
    using chess::core::PieceType;

    // Для простоты используем ASCII: заглавные = белые, строчные = чёрные
    char c = '.';
    switch (piece.type) {
        case PieceType::King:   c = 'K'; break;
        case PieceType::Queen:  c = 'Q'; break;
        case PieceType::Rook:   c = 'R'; break;
        case PieceType::Bishop: c = 'B'; break;
        case PieceType::Knight: c = 'N'; break;
        case PieceType::Pawn:   c = 'P'; break;
    }

    // Чёрные фигуры — строчные буквы
    if (piece.color == Color::Black) {
        c = static_cast<char>(c + ('a' - 'A'));
    }

    return c;
}

// Рисуем доску: ряды сверху вниз (8 → 1), файлы слева направо (a → h)
void Renderer::render_board(const core::Board& board) const {
    output_ << "\n";

    // rank идёт от 7 (ряд 8) до 0 (ряд 1) — рисуем сверху вниз
    for (int rank = 7; rank >= 0; --rank) {
        // Номер ряда слева
        output_ << (rank + 1) << " ";

        for (int file = 0; file < 8; ++file) {
            const auto piece = board.piece_at(file, rank);
            if (piece.has_value()) {
                output_ << piece_char(*piece);
            } else {
                // Шахматная клетка — чередуем символы для наглядности
                const bool light_square = (file + rank) % 2 != 0;
                output_ << (light_square ? '.' : ',');
            }
            output_ << ' ';
        }

        output_ << "\n";
    }

    // Подпись файлов снизу
    output_ << "  a b c d e f g h\n\n";
}

// Рисуем всё состояние: доска + чья очередь ходить
void Renderer::render_state(const core::State& state) const {
    render_board(state.board);

    const std::string_view side =
        state.side_to_move == core::Color::White ? "White" : "Black";
    output_ << side << " to move\n";
}

// Выводим список ходов в формате "e2e4, d7d5, ..."
void Renderer::render_moves(const std::vector<core::Move>& moves) const {
    if (moves.empty()) {
        output_ << "No moves available.\n";
        return;
    }

    output_ << "Available moves (" << moves.size() << "):\n";

    for (size_t i = 0; i < moves.size(); ++i) {
        const auto& move = moves[i];

        // Преобразуем числа обратно в буквы: file 0 → 'a', rank 0 → '1'
        const char from_file = static_cast<char>('a' + move.from.file);
        const char from_rank = static_cast<char>('1' + move.from.rank);
        const char to_file   = static_cast<char>('a' + move.to.file);
        const char to_rank   = static_cast<char>('1' + move.to.rank);

        output_ << from_file << from_rank << to_file << to_rank;

        // Если ход с превращением — добавляем букву фигуры
        if (move.promotion.has_value()) {
            output_ << piece_char(*move.promotion);
        }

        // Разделяем ходы пробелом, после последнего — перенос строки
        if (i + 1 < moves.size()) {
            output_ << ' ';
        }
    }

    output_ << "\n";
}

void Renderer::render_message(std::string_view message) const {
    output_ << message << "\n";
}

void Renderer::render_error(std::string_view message) const {
    output_ << "Error: " << message << "\n";
}

// Приглашение к вводу — выводим без переноса строки, чтобы курсор остался рядом
void Renderer::render_prompt() const {
    output_ << "> " << std::flush;
}

} // namespace chess::cli

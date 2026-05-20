#include "chess/cli/repl.hpp"

#include "chess/cli/command.hpp"

#include <iostream>
#include <string>

namespace chess::cli {

// Конструктор: получаем ссылки на сессию и потоки ввода/вывода
// Renderer создаём здесь — передаём ему поток вывода
Repl::Repl(Session& session, std::istream& input, std::ostream& output)
    : session_(session)
    , input_(input)
    , renderer_(output)
{}

// Главный цикл: читаем строку → парсим → обрабатываем → выводим ответ
void Repl::run() {
    renderer_.render_message("Chess CLI. Type 'help' for commands.");

    // Показываем начальное состояние доски
    renderer_.render_state(session_.game().state());

    std::string line;

    while (true) {
        renderer_.render_prompt();

        // Читаем строку. Если поток закрылся (Ctrl+D) — выходим
        if (!std::getline(input_, line)) {
            break;
        }

        const Command command = session_.parse(line);

        // ExitCommand — выходим из цикла немедленно
        if (std::holds_alternative<ExitCommand>(command)) {
            renderer_.render_message("Goodbye!");
            break;
        }

        const std::string response = session_.handle(command);

        // После успешного хода или команды board — показываем доску
        const bool show_board =
            std::holds_alternative<BoardCommand>(command) ||
            (std::holds_alternative<MoveCommand>(command) && response == "OK") ||
            std::holds_alternative<UndoCommand>(command) ||
            std::holds_alternative<ResetCommand>(command);

        if (show_board) {
            renderer_.render_state(session_.game().state());
        }

        // Выводим ответ (если он не пустой)
        if (!response.empty() && response != "OK") {
            renderer_.render_message(response);
        }
    }
}

} // namespace chess::cli

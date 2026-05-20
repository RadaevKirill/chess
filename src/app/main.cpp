#include "chess/app/main.hpp"

#include "chess/cli/repl.hpp"
#include "chess/cli/session.hpp"

#include <iostream>

namespace chess::app {

int run() {
    // Создаём сессию — она хранит состояние игры и умеет обрабатывать команды
    chess::cli::Session session;

    // REPL (Read-Eval-Print Loop) — бесконечный цикл чтения и выполнения команд
    // std::cin — стандартный ввод (клавиатура), std::cout — стандартный вывод
    chess::cli::Repl repl(session, std::cin, std::cout);
    repl.run();

    return 0;
}

} // namespace chess::app

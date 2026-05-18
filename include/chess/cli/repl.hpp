#pragma once

#include "chess/cli/renderer.hpp"
#include "chess/cli/session.hpp"

#include <iosfwd>

namespace chess::cli {

    class Repl {
    public:
        Repl(Session& session, std::istream& input, std::ostream& output);

        void run();

    private:
        Session& session_;
        std::istream& input_;
        Renderer renderer_;
    };

}

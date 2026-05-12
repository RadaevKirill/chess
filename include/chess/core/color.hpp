#pragma once

namespace chess::core {

enum class Color {
    White,
    Black
};

[[nodiscard]] constexpr Color opposite(Color color) {
    return color == Color::White ? Color::Black : Color::White;
}

}

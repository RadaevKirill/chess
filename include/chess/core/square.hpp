#pragma once

namespace chess::core {

struct Square {
    int file; // 0..7, где 0 = a
    int rank; // 0..7, где 0 = 1

    [[nodiscard]] constexpr bool is_valid() const {
        return file >= 0 && file < 8 && rank >= 0 && rank < 8;
    }
};

[[nodiscard]] constexpr bool operator==(Square lhs, Square rhs) {
    return lhs.file == rhs.file && lhs.rank == rhs.rank;
}

}

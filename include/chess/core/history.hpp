#pragma once

#include <array>
#include <cstddef>

#include "chess/core/move.hpp"
#include "chess/core/record.hpp"

namespace chess::core {
    class History {
    public:
        void add_record(const Record& record);
        void remove_last_record();
        const Record& get_record(size_t index);

        [[nodiscard]] const Record& last_record() const;
        [[nodiscard]] size_t history_count() const;
    
    private:
        std::array<Record, 1024> moves_;
        size_t move_count_ = 0;
    };
}
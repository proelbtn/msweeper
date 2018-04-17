#pragma once

#include <cstdint>

namespace curses {
    extern const uint32_t AT_RESET;
    extern const uint32_t AT_BOLD;
    extern const uint32_t AT_UNDERLINE;
    extern const uint32_t FG_BLACK;
    extern const uint32_t FG_RED;
    extern const uint32_t FG_GREEN;
    extern const uint32_t FG_YELLOW;
    extern const uint32_t FG_BLUE;
    extern const uint32_t FG_MAGENTA;
    extern const uint32_t FG_CYAN;
    extern const uint32_t FG_WHITE;
    extern const uint32_t BG_BLACK;
    extern const uint32_t BG_RED;
    extern const uint32_t BG_GREEN;
    extern const uint32_t BG_YELLOW;
    extern const uint32_t BG_BLUE;
    extern const uint32_t BG_MAGENTA;
    extern const uint32_t BG_CYAN;
    extern const uint32_t BG_WHITE;

    void clear();
    void cursor(int x, int y);
    void chctl(uint32_t flag);
}
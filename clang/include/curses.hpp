#pragma once

#include <cstdint>

namespace curses {
    extern const unsigned int AT_RESET;
    extern const unsigned int AT_BOLD;
    extern const unsigned int AT_UNDERLINE;
    extern const unsigned int FG_BLACK;
    extern const unsigned int FG_RED;
    extern const unsigned int FG_GREEN;
    extern const unsigned int FG_YELLOW;
    extern const unsigned int FG_BLUE;
    extern const unsigned int FG_MAGENTA;
    extern const unsigned int FG_CYAN;
    extern const unsigned int FG_WHITE;
    extern const unsigned int BG_BLACK;
    extern const unsigned int BG_RED;
    extern const unsigned int BG_GREEN;
    extern const unsigned int BG_YELLOW;
    extern const unsigned int BG_BLUE;
    extern const unsigned int BG_MAGENTA;
    extern const unsigned int BG_CYAN;
    extern const unsigned int BG_WHITE;

    void clear();
    void cursor(int x, int y);
    void chctl(unsigned int flag);
}
#include "curses.hpp"

#include <cstdio>
#include <cstdint>

namespace curses {
    const uint32_t AT_RESET      = 1 << 0;
    const uint32_t AT_BOLD       = 1 << 1;
    const uint32_t AT_UNDERLINE  = 1 << 2;
    const uint32_t FG_BLACK      = 1 << 8;
    const uint32_t FG_RED        = 2 << 8;
    const uint32_t FG_GREEN      = 3 << 8;
    const uint32_t FG_YELLOW     = 4 << 8;
    const uint32_t FG_BLUE       = 5 << 8;
    const uint32_t FG_MAGENTA    = 6 << 8;
    const uint32_t FG_CYAN       = 7 << 8;
    const uint32_t FG_WHITE      = 8 << 8;
    const uint32_t BG_BLACK      = 1 << 16;
    const uint32_t BG_RED        = 2 << 16;
    const uint32_t BG_GREEN      = 3 << 16;
    const uint32_t BG_YELLOW     = 4 << 16;
    const uint32_t BG_BLUE       = 5 << 16;
    const uint32_t BG_MAGENTA    = 6 << 16;
    const uint32_t BG_CYAN       = 7 << 16;
    const uint32_t BG_WHITE      = 8 << 16;

    void clear() {
        printf("\033[2J");
        cursor(0, 0);
    }

    void cursor(int x, int y) {
        printf("\033[%d;%dH", y, x);
    }

    void chctl(uint32_t flag) {
        switch (flag & (0xF << 8)) {
            case FG_BLACK:
                printf("\033[30m"); break;
            case FG_RED:
                printf("\033[31m"); break;
            case FG_GREEN:
                printf("\033[32m"); break;
            case FG_YELLOW:
                printf("\033[33m"); break;
            case FG_BLUE:
                printf("\033[34m"); break;
            case FG_MAGENTA:
                printf("\033[35m"); break;
            case FG_CYAN:
                printf("\033[36m"); break;
            case FG_WHITE:
                printf("\033[37m"); break;
        }

        switch (flag & (0xF << 16)) {
            case BG_BLACK:
                printf("\033[40m"); break;
            case BG_RED:
                printf("\033[41m"); break;
            case BG_GREEN:
                printf("\033[42m"); break;
            case BG_YELLOW:
                printf("\033[43m"); break;
            case BG_BLUE:
                printf("\033[44m"); break;
            case BG_MAGENTA:
                printf("\033[45m"); break;
            case BG_CYAN:
                printf("\033[46m"); break;
            case BG_WHITE:
                printf("\033[47m"); break;
        }

        if (flag & curses::AT_BOLD) printf("\033[1m");
        if (flag & curses::AT_UNDERLINE) printf("\033[4m");

        if (flag & curses::AT_RESET) printf("\033[0m");
    }
}
#include <array>
#include <functional>
#include <iostream>
#include <limits>

#include "curses.hpp"
#include "msweeper.hpp"

const char *err_msg_width  = "[ERR] Constraint Error (0 <= Width)";
const char *err_msg_height = "[ERR] Constraint Error (0 <= Height)";
const char *err_msg_bomb   = "[ERR] Constraint Error (0 <= Bomb <= Width * Height)";
const char *err_msg_x      = "[ERR] Constraint Error (0 <= X <= Width)";
const char *err_msg_y      = "[ERR] Constraint Error (0 <= Y <= Height)";
const char *err_msg_open   = "[ERR] Invalid Argument (This cell was opened)";

void display_cell(msweeper& ms, int x, int y) {
    uint32_t flag = 0;
    int t = ms.at(x, y);

    switch(t) {
        case 1: flag |= curses::AT_BOLD | curses::FG_YELLOW; break;
        case 2: flag |= curses::AT_BOLD | curses::FG_GREEN; break;
        case 3: flag |= curses::AT_BOLD | curses::FG_CYAN; break;
        case 4: flag |= curses::AT_BOLD | curses::FG_CYAN; break;
        case 5: flag |= curses::AT_BOLD | curses::FG_BLUE; break;
        case 6: flag |= curses::AT_BOLD | curses::FG_BLUE; break;
        case 7: flag |= curses::AT_BOLD | curses::FG_RED; break;
        case 8: flag |= curses::AT_BOLD | curses::FG_RED; break;
        default: flag |= curses::FG_WHITE; break;
    }
    curses::chctl(flag);
    putchar(".12345678#"[t]);

    curses::chctl(curses::AT_RESET);
}

void display_map(msweeper& ms) {
    putchar(' ');
    for(int i = 0; i < ms.width; i++) {
        if (i % 5 == 0) putchar('|');
        putchar("0    5    "[i % 10]);
    }
    putchar('\n');

    for(int y = 0; y < ms.height; y++) {
        if(y % 5 == 0) {
            putchar('-');
            for(int x = 0; x < ms.width; x++) {
                if (x % 5 == 0) putchar('+');
                putchar('-');
            }
            putchar('\n');
        }

        putchar("0    5    "[y % 10]);
        for(int x = 0; x < ms.width; x++) {
            if(x % 5 == 0) putchar('|');
            display_cell(ms, x, y);
        }
        putchar('\n');
    }
}

void get_integer(const char *s, int &v) {
    bool f;
    size_t sz;
    std::string t;

    do {
        f = true;
        try {
            std::cout << s << " : ";
            std::cin >> t;
            v = std::stoi(t, &sz);
            if (t.size() != sz) throw std::exception();
            f = false;
        } catch (std::exception& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERR] Runtime Error (expected ONLY Integer)" << std::endl;
        }
    } while (f);
}

void get_integer(const char *s, int &v, std::function<bool(int)> f) {
    do get_integer(s, v); while(!f(v));
}

msweeper init_msweeper() {
    int width, height, bomb;

    get_integer("Width", width, [](int t) {
            bool r = 0 <= t;
            if (!r) std::cout << err_msg_width << std::endl;
            return r;
        });

    get_integer("Height", height, [](int t) {
            bool r = 0 <= t;
            if (!r) std::cout << err_msg_height << std::endl;
            return r;
        });

    get_integer("Bomb", bomb, [=](int t) {
            bool r = 0 <= t && t <= width * height;
            if (!r) std::cout << err_msg_bomb << std::endl;
            return r;
        });

    return msweeper(width, height, bomb);
}

int main() {
    int x, y;
    bool f;

    std::cin.exceptions(std::ios::failbit);

    msweeper ms = init_msweeper();

    while(ms.get_status() == msweeper::status::MS_OTHER) {
        curses::clear();
        display_map(ms);

        do {
            get_integer("X", x, [&](int t) {
                    bool r = 0 <= t && t <= ms.width;
                    if (!r) std::cout << err_msg_x << std::endl;
                    return r;
                });
            get_integer("Y", y, [&](int t) {
                    bool r = 0 <= t && t <= ms.height;
                    if (!r) std::cout << err_msg_y << std::endl;
                    return r;
                });

            if (!(f = ms.open(x, y))) std::cout << err_msg_open << std::endl;
        } while(!f);
    }

    if(ms.get_status() == msweeper::status::MS_GAME_CLEAR) std::cout << "GAME CLEAR!" << std::endl;
    else std::cout << "GAME OVER..." << std::endl;

    return 0;
}

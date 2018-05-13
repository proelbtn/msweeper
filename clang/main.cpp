#include <array>
#include <functional>
#include <iostream>
#include <limits>

#include "curses.hpp"
#include "msweeper.hpp"

const char *num_bar = "0    5    ";
const char *cell = ".12345678#";

void flag_color_set(int t, uint32_t &flag) {
    switch(t) {
        case 1: flag |= curses::FG_YELLOW; break;
        case 2: flag |= curses::FG_GREEN; break;
        case 3: flag |= curses::FG_CYAN; break;
        case 4: flag |= curses::FG_CYAN; break;
        case 5: flag |= curses::FG_BLUE; break;
        case 6: flag |= curses::FG_BLUE; break;
        case 7: flag |= curses::FG_RED; break;
        case 8: flag |= curses::FG_RED; break;
        default: flag |= curses::FG_WHITE; break;
    }
}

void display(msweeper& ms) {
    curses::chctl(curses::AT_RESET);
    
    printf(" ");
    for(int i = 0; i < ms.width; i++) printf("%s%c", i % 5 == 0 ? "|" : "", (i % 10)[num_bar]);
    putchar('\n');

    for(int y = 0; y < ms.height; y++) {
        if(y % 5 == 0) {
            curses::chctl(curses::AT_RESET);
            printf("-");
            for(int x = 0; x < ms.width; x++) printf("%s", x % 5 == 0 ? "+-" : "-");
            putchar('\n');
        }

        putchar((y % 10)[num_bar]);
        for(int x = 0; x < ms.width; x++) {
            uint32_t flag = 0;
            int t = ms.at(x, y);
            if (t == msweeper::MS_CELL_INVALID) throw "Error!";

            curses::chctl(curses::AT_RESET);
            printf("%s", x % 5 == 0 ? "|" : "");
            flag = 0;
            flag |= (1 <= t && t <= 8 ? curses::AT_BOLD : 0);
            flag_color_set(t, flag);
            curses::chctl(flag);

            putchar(t[cell]);
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

int main() {
    int x, y, width, height, bomb;

    std::cin.exceptions(std::ios::failbit);

    get_integer("Width", width, [](int t) {
            bool r = 0 <= t;
            if (!r) std::cout << "[ERR] Constraint Error (0 <= Width)" << std::endl;
            return r;
        });

    get_integer("Height", height, [](int t) {
            bool r = 0 <= t;
            if (!r) std::cout << "[ERR] Constraint Error (0 <= Height)" << std::endl;
            return r;
        });

    get_integer("Bomb", bomb, [=](int t) {
            bool r = 0 <= t && t <= width * height;
            if (!r) std::cout << "[ERR] Constraint Error (0 <= Bomb <= Width * Height)" << std::endl;
            return r;
        });

    try {
        msweeper ms(width, height, bomb);

        while(ms.get_status() == msweeper::status::MS_NONE) {
            curses::clear();
            display(ms);

            get_integer("X", x, [&](int t) {
                    bool r = 0 <= t && t <= ms.width;
                    if (!r) std::cout << "[ERR] Constraint Error (0 <= X <= Width)" << std::endl;
                    return r;
                });
            get_integer("Y", y, [&](int t) {
                    bool r = 0 <= t && t <= ms.height;
                    if (!r) std::cout << "[ERR] Constraint Error (0 <= Y <= Height)" << std::endl;
                    return r;
                });

            ms.open(x, y);
        }

        if(ms.get_status() == msweeper::status::MS_GAME_CLEAR) std::cout << "GAME CLEAR!" << std::endl;
        else std::cout << "GAME OVER..." << std::endl;
    } 
    catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

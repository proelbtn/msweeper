#include <array>
#include <iostream>

#include "curses.hpp"
#include "msweeper.hpp"

void display(msweeper& ms) {
    uint32_t flag;

    printf(" ");
    for(int i = 0; i < ms.width; i++) {
        if(i % 10 == 0) putchar('0');
        else if(i % 10 == 5) putchar('5');
        else putchar(' ');
    }
    printf("\n");
    for(int y = 0; y < ms.height; y++) {
        if(y % 10 == 0) putchar('0');
        else if(y % 10 == 5) putchar('5');
        else putchar(' ');

        for(int x = 0; x < ms.width; x++) {
            int t = ms.at(x, y);

            curses::chctl(curses::AT_RESET);
            flag = 0;
            flag |= (1 <= t && t <= 8 ? curses::AT_BOLD : 0);
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
            curses::chctl(flag);

            putchar("_12345678."[ms.at(x, y)]);
        }

        putchar('\n');
    }
}

void get_integer(const char *s, int &v) {
    std::cout << s << " : ";
    std::cin >> v;
}

int main() {
    int x, y, width, height, bomb;

    get_integer("Width", width);
    get_integer("Height", height);
    get_integer("Bomb", bomb);

    msweeper ms(width, height, bomb);

    while(ms.get_status() == msweeper::status::MS_NONE) {
        curses::clear();
        display(ms);

        get_integer("X", x);
        get_integer("Y", y);

        ms.open(x, y);
    }

    if(ms.get_status() == msweeper::status::MS_GAME_CLEAR) std::cout << "GAME CLEAR!" << std::endl;
    else std::cout << "GAME OVER..." << std::endl;
}

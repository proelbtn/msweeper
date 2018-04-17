#include <array>
#include <iostream>

#include "msweeper.hpp"

void display(msweeper& ms) {
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
        display(ms);

        get_integer("X", x);
        get_integer("Y", y);

        ms.open(x, y);
    }

    return ms.get_status() == msweeper::status::MS_GAME_CLEAR ? 0 : -1;
}

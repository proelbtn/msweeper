#include <array>
#include <iostream>

#include "msweeper.hpp"

void display(msweeper& ms) {
    printf(" ");
    for(int i = 0; i < 8; i++) printf("%d", i);
    printf("\n");
    for(int y = 0; y < 8; y++) {
        printf("%d", y);
        for(int x = 0; x < 8; x++) {
            printf("%c", ms.at(x, y));
        }
        printf("\n");
    }
}

int main() {
    msweeper ms(5);

    while(ms.get_status() == msweeper::status::MS_NONE) {
        display(ms);

        int x, y;
        std::cin >> x >> y;

        ms.open(x, y);
    }

    return ms.get_status() == msweeper::status::MS_GAME_CLEAR ? 0 : -1;
}
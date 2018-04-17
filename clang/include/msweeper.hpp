#pragma once

#include <array>

class msweeper {
public:
    typedef std::array<bool, 64> map;

    enum status {
        MS_GAME_OVER,
        MS_GAME_CLEAR,
        MS_NONE
    };

    msweeper(int bnum);

    char at(int x, int y);
    bool open(int x, int y);
    msweeper::status get_status();

private:
    msweeper::map bomb;
    msweeper::map opened;
};
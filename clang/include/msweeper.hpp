#pragma once

#include <vector>

class msweeper {
public:
    typedef std::vector<bool> map;

    enum cell_status {
        MS_CELL_ZERO = 0,
        MS_CELL_ONE,
        MS_CELL_TWO,
        MS_CELL_THREE,
        MS_CELL_FOUR,
        MS_CELL_FIVE,
        MS_CELL_SIX,
        MS_CELL_SEVEN,
        MS_CELL_EIGHT,
        MS_CELL_NOT_OPENED
    };

    enum status {
        MS_GAME_OVER,
        MS_GAME_CLEAR,
        MS_NONE
    };

    const uint32_t width;
    const uint32_t height;

    msweeper(uint32_t width, uint32_t height, uint32_t bnum);

    msweeper::cell_status at(int x, int y);
    bool open(int x, int y);
    msweeper::status get_status();

private:
    msweeper::map bomb;
    msweeper::map opened;

    bool is_range(int x, int y);
};
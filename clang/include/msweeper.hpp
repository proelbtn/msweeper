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
        MS_CELL_NOT_OPENED,
        MS_CELL_BOMB = -1,
    };

    enum status {
        MS_GAME_OVER,
        MS_GAME_CLEAR,
        MS_OTHER
    };

    const unsigned int width;
    const unsigned int height;

    msweeper(unsigned int width, unsigned int height, unsigned int bnum);

    msweeper::cell_status at(int x, int y) const;
    bool open(int x, int y);
    msweeper::status get_status() const;

private:
    msweeper::map bomb;
    msweeper::map opened;

    bool is_range(int x, int y) const;
};
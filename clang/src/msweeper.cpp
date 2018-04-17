#include "msweeper.hpp"

#include <algorithm>
#include <array>
#include <random>

msweeper::msweeper(uint32_t width, uint32_t height, uint32_t bnum) :
    width(width), height(height), bomb(width * height, false), opened(width * height, false) 
{
    if (!(bnum <= width * height)) throw 0;

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

    for (int i = 0; i < bnum; i++) bomb.at(i) = true;
    std::shuffle(bomb.begin(), bomb.end(), std::default_random_engine(seed));
}

msweeper::cell_status msweeper::at(int x, int y) {
    if (!opened.at(y * width + x)) return msweeper::cell_status::MS_CELL_NOT_OPENED;

    int c = 0;

    for (int dx = -1; dx < 2; dx++) {
        for (int dy = -1; dy < 2; dy++) {
            int nx = x + dx, ny = y + dy;
            if ((dx == 0 && dy == 0) || !is_range(nx, ny)) continue;
            if (bomb.at(ny * width + nx)) c++;
        }
    }

    return (msweeper::cell_status)c;
}

bool msweeper::open(int x, int y) {
    int pos = y * width + x;

    if(opened.at(pos)) return false;

    opened.at(pos) = true;

    if (at(x, y) == MS_CELL_ZERO) {
        for (int dx = -1; dx < 2; dx++) {
            for (int dy = -1; dy < 2; dy++) {
                int nx = x + dx, ny = y + dy;
                if ((dx == 0 && dy == 0) || !is_range(nx, ny)) continue;
                if (!opened.at(ny * width + nx)) open(nx, ny);
            }
        }
    }

    return true;
}

msweeper::status msweeper::get_status() {
    bool flag = true;
    for(int i = 0; i < width * height; i++) {
        if (bomb[i] && opened[i]) return MS_GAME_OVER;
        if (!bomb[i] && !opened[i]) flag = false;
    }
    return flag ? MS_GAME_CLEAR : MS_NONE;
}

bool msweeper::is_range(int x, int y) {
    return 0 <= x && x < width && 0 <= y && y < height;
}
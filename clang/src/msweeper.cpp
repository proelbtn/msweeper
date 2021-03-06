#include "msweeper.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <random>
#include <stdexcept>

msweeper::msweeper(unsigned int width, unsigned int height, unsigned int bnum) :
    width(width), height(height), bomb(width * height, false), opened(width * height, false) 
{
    if (!(0 <= bnum && bnum <= width * height)) 
        throw std::invalid_argument("expected 0 <= bnum <= width * height");

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

    for (int i = 0; i < bnum; i++) bomb[i] = true;
    std::shuffle(bomb.begin(), bomb.end(), std::default_random_engine(seed));
}

msweeper::cell_status msweeper::at(int x, int y) const {
    if (!is_range(x, y)) throw std::invalid_argument("expected is_range(x, y) == true");

    int pos = y * width + x;

    if (!opened[pos]) return msweeper::MS_CELL_NOT_OPENED;
    if (bomb[pos]) return msweeper::MS_CELL_BOMB;

    int c = 0;
    for (int dx = -1; dx < 2; dx++) {
        for (int dy = -1; dy < 2; dy++) {
            int nx = x + dx, ny = y + dy, npos = ny * width + nx;
            if (is_range(nx, ny) && bomb[npos]) c++;
        }
    }

    return (msweeper::cell_status)c;
}

bool msweeper::open(int x, int y) {
    if(!is_range(x, y)) throw std::invalid_argument("expected is_range(x, y) == true");

    int pos = y * width + x;
    if(opened[pos]) return false;

    opened[pos] = true;
    if (at(x, y) == MS_CELL_ZERO) {
        for (int dx = -1; dx < 2; dx++) {
            for (int dy = -1; dy < 2; dy++) {
                int nx = x + dx, ny = y + dy;
                if (!(dx == 0 && dy == 0) && is_range(nx, ny)) open(nx, ny);
            }
        }
    }

    return true;
}

msweeper::status msweeper::get_status() const {
    bool flag = true;
    for(int i = 0; i < width * height; i++) {
        if (bomb[i] && opened[i]) return MS_GAME_OVER;
        if (!bomb[i] && !opened[i]) flag = false;
    }
    return flag ? MS_GAME_CLEAR : MS_OTHER;
}

bool msweeper::is_range(int x, int y) const {
    return 0 <= x && x < width && 0 <= y && y < height;
}

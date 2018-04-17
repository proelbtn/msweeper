#include "msweeper.hpp"

#include <algorithm>
#include <array>
#include <random>

msweeper::msweeper(int bnum) : bomb(), opened() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();

    for (int i = 0; i < bnum; i++) bomb.at(i) = true;
    std::shuffle(bomb.begin(), bomb.end(), std::default_random_engine(seed));
}

char msweeper::at(int x, int y) {
    if (!opened.at(y * 8 + x)) return '.';

    int c = 0;

    for (int dx = -1; dx < 2; dx++) {
        for (int dy = -1; dy < 2; dy++) {
            int nx = x + dx, ny = y + dy;
            if (dx == 0 && dy == 0) continue;
            if (!(0 <= nx && nx < 8) || !(0 <= ny && ny < 8)) continue;
            if (bomb.at(ny * 8 + nx)) c++;
        }
    }

    return "012345678"[c];
}

bool msweeper::open(int x, int y) {
    int pos = y * 8 + x;

    if(opened.at(pos)) return false;

    opened.at(pos) = true;
    return true;
}

msweeper::status msweeper::get_status() {
    bool flag = true;
    for(int i = 0; i < 64; i++) {
        if (bomb[i] && opened[i]) return MS_GAME_OVER;
        if (!bomb[i] && !opened[i]) flag = false;
    }
    return flag ? MS_GAME_CLEAR : MS_NONE;
}
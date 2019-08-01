#include "tile.h"
#define NDEBUG
#include <assert.h>

using namespace reversi;

void tile::flipOccupant() {
    assert(isOccupied(piece));
    piece = flip(piece);
}

tile::~tile() {
    delete(inf);
}

info::~info() {
    for (auto it = adjEmptyTiles.cbegin(); it != adjEmptyTiles.cend(); it++) {
        delete(*it);
    }
}
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

tile::info::~info() {
    for (auto it = adjEmptyTiles.cbegin(); it != adjEmptyTiles.cend(); it++) {
        delete(*it);
    }
}

tile::tile(const tile &copy):piece(copy.piece) {
    if (copy.inf == nullptr)
    {
        inf = nullptr;
    }
    else
    {
        inf = new tile::info(*copy.inf);
    }
}

tile::info::info(const info &copy):position(copy.position),\
freeSpaces(copy.freeSpaces) {
    for (auto &&mv : copy.adjEmptyTiles)
    {
        adjEmptyTiles.push_front(new move(*mv));
    }
}
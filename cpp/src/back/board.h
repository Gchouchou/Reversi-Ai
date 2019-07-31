#ifndef BOARD_HEADER
#define BOARD_HEADER
#include "game_settings.h"
#include "tile.h"
#include "coordinate.h"
#include "occupant.h"
#include "move.h"

#include <array>
#include <list>

namespace reversi
{
    class board
    {
    private:
        std::array<std::array<tile*,BOARD_SIDE_LENGTH>*,BOARD_SIDE_LENGTH> fullboard;
        // keep track of edge black/white tiles
        std::list<tile*> whiteEdgeTiles;
        std::list<tile*> blackEdgeTiles;
        occupant who;
        int turnsLeft;
    public:
        const tile *getTile(const coordinate &coord);
        void playTurn(const coordinate &coord);
        const std::list<const move*> *getValidMoves();
        board();
        ~board();
    };
} // namespace reversi


#endif
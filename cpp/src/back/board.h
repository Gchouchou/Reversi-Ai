#ifndef BOARD_HEADER
#define BOARD_HEADER
#include "game_settings.h"
#include "tile.h"
#include "coordinate.h"
#include "occupant.h"
#include "move.h"

#include <array>
#include <forward_list>

namespace reversi
{
    class board
    {
    private:
        // type defs
        typedef std::forward_list<tile*> tileList;
        typedef std::forward_list<move*> moveList;
        typedef std::forward_list<const coordinate*> constCoordList;

        // class members
        std::array<std::array<tile*,BOARD_SIDE_LENGTH>*,BOARD_SIDE_LENGTH> fullboard;
        // keep track of edge black/white tiles
        tileList whiteEdgeTiles;
        tileList blackEdgeTiles;
        occupant who;
        moveList validMoves;
        int turnsLeft;
        occupant winner;
        bool isGameOver;

        // place a piece at a coordinate
        void placePiece(const coordinate &pos, const occupant piece);
        // get the right list
        tileList *getList(const occupant color);
        // find the valid moves after playing a turn
        void findValidMoves();
        // tests if this is a possible move
        bool checkDirection(const coordinate &start, const direction dir, const occupant player);
        // clear list and free memory
        void clearValidMoves();
        // flip all the tiles in a direction, THIS FUNCTION DOES NOT HAVE SAFETY CHECK
        void flipTiles(const coordinate &start, const direction dir, const occupant player);

    public:
        const occupant getWinner() { return winner; }
        const bool gameOver() { return isGameOver; }

        const tile *getTile(const coordinate &coord) const;
        // returns true if the move is valid
        bool playTurn(const coordinate &coord);
        // returns a list of coordinates, must be memory managed
        const constCoordList *getValidMoves();
        board();
        // board(const board &copy);
        ~board();
    };
} // namespace reversi


#endif
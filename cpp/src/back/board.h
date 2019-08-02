#ifndef BOARD_HEADER
#define BOARD_HEADER
#include "game_settings.h"
#include "tile.h"
#include "coordinate.h"
#include "occupant.h"
#include "move.h"

#include <array>
#include <forward_list>
#include <vector>

namespace reversi
{
    typedef std::vector<const coordinate*> validMoveList;
    
    // template deleter
    template <class t>
    void clearList(std::forward_list<t*> &list){
        while (!list.empty())
        {
            t *ptr = list.front();
            list.pop_front();
            delete(ptr);
        }
    }
    template <class t>
    void clearList(std::vector<t*> &list){
        while (!list.empty())
        {
            t *ptr = list.front();
            list.pop_front();
            delete(ptr);
        }
    }
    class board
    {
    private:
        // type defs
        typedef std::forward_list<tile*> tileList;
        typedef std::forward_list<move*> moveList;

        // class members
        std::array<std::array<tile*,BOARD_SIDE_LENGTH>*,BOARD_SIDE_LENGTH> fullboard;
        // keep track of edge black/white tiles
        tileList whiteEdgeTiles;
        tileList blackEdgeTiles;
        occupant who;
        moveList validMoves;
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
        // set winner
        void setGameEnd();
        // flip all the tiles in a direction, THIS FUNCTION DOES NOT HAVE SAFETY CHECK
        void flipTiles(const coordinate &start, const direction dir, const occupant player);

    public:
        const occupant getWinner() { return winner; }
        const occupant getWho() { return who; }
        const bool gameOver() { return isGameOver; }

        const tile *getTile(const coordinate &coord) const;
        // returns true if the game ends
        bool playTurn(const coordinate &coord);
        // returns a list of coordinates, must be memory managed
        void getValidMoves (validMoveList &list) const;
        board();
        // copy constructor
        board(const board &copy);
        ~board();
    };
} // namespace reversi


#endif
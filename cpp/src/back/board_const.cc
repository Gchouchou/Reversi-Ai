#include "board.h"

using namespace reversi;
using namespace std;

board::board() {
    typedef array<tile*,BOARD_SIDE_LENGTH> tilearray;

    // for placing pieces after
    const int half = (BOARD_SIDE_LENGTH-1)/2;
    coordinate c(half,half);

    occupant o;
    for (int i = 0; i < BOARD_SIDE_LENGTH; i++)
    {
        tilearray *column = new tilearray();
        for (int j = 0; j < BOARD_SIDE_LENGTH; j++)
        {
            tile *t = new tile();
            column->at(j) = t;
        }
        fullboard.at(i) = column;
    }
    
    // now place the 4 blocks in the middle
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2;  j++)
        {
            c.x = half+i; c.y = half+j;
            if ((i+j)%2 == 1)
            {
                o = white;
            } else {
                o = black;
            }
            placePiece(c,o);
        }
    }
    // initialize the rest
    who = white;
    winner = empty;
    isGameOver = false;
    gameStarted = false;
    findValidMoves();
}

board::~board() {
    // delete all the tiles
    for (size_t i = 0; i < BOARD_SIDE_LENGTH; i++)
    {
        for (size_t j = 0; j < BOARD_SIDE_LENGTH; j++)
        {
            delete(fullboard[i]->at(j));
        }
        // delete the array
        delete(fullboard[i]);
    }
    clearValidMoves();
}

board::board(const board &copy): who(copy.who),winner(copy.winner),\
isGameOver(copy.isGameOver) {
    typedef array<tile*,BOARD_SIDE_LENGTH> tilearray;

    // do the same thing as the constructor but copy the tiles
    for (int i = 0; i < BOARD_SIDE_LENGTH; i++)
    {
        tilearray *column = new tilearray();
        for (int j = 0; j < BOARD_SIDE_LENGTH; j++)
        {
            tile *t = new tile(*copy.fullboard[i]->at(j));
            column->at(j) = t;
        }
        fullboard.at(i) = column;
    }

    // use the positions to get the appropriate tiles
    for (auto &&wTiles : copy.whiteEdgeTiles)
    {
        whiteEdgeTiles.push_front(
            fullboard[wTiles->inf->position.x]->at(wTiles->inf->position.y) \
        );
    }
    for (auto &&bTiles : copy.blackEdgeTiles)
    {
        blackEdgeTiles.push_front(
            fullboard[bTiles->inf->position.x]->at(bTiles->inf->position.y) \
        );
    }

    // the moveList is simple to do
    for (auto &&vmoves : copy.validMoves)
    {
        validMoves.push_front(new move(*vmoves));
    }
}
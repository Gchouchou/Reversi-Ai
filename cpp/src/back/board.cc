#include "board.h"
#include "direction.h"
#define NDEBUG
#include <assert.h>

using namespace reversi;

const tile *board::getTile(const coordinate &coord) const {
    return fullboard[coord.x]->at(coord.y);
}

const board::constCoordList *board::getValidMoves() {
    constCoordList *list = new constCoordList();
    for (auto &&mov : validMoves)
    {
        list->push_front(new coordinate((*mov).position));
    }
    return list;
}


bool board::playTurn(const coordinate &coord) {
    // if the game is over we don't need to do anything
    if (isGameOver)
    {
        return true;
    }
    // check if the coordinate is valid
    move *playedMove = nullptr;
    // search the list
    for (auto it = validMoves.cbegin(); it != validMoves.cend(); it++) {
        if ((*it)->position == coord)
        {
            playedMove = *it;
            break;
        }
    }
    assert(playedMove != nullptr);
    
    // the coordinate given is valid
    flipTiles(playedMove->position,playedMove->mainDir,who);
    // check for additionnal directions
    if (playedMove->directions != nullptr)
    {
        for (auto &&dir : *(playedMove->directions))
        {
            if (checkDirection(playedMove->position,dir,who))
            {
                flipTiles(playedMove->position,dir,who);
            }
        }
    }
    // place the piece
    placePiece(playedMove->position,who);
    // reverse turns
    who = flip(who);
    // check valid moves, if there is none go back to first player
    findValidMoves();
    if (validMoves.empty())
    {
        who = flip(who);
        findValidMoves();
        // check if both players have no more moves
        if (validMoves.empty())
        {
            setGameEnd();
            return true;
        }
    }
    return false;
}
#include "board.h"
#include "direction.h"

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
        return false;
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
    if (playedMove != nullptr)
    {
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
            if (validMoves.empty())
            {
                isGameOver = true;
                // tally points
                int w=0,b=0;
                for (int i = 0; i < BOARD_SIDE_LENGTH; i++)
                {
                    for (int j = 0; j < BOARD_SIDE_LENGTH; j++)
                    {
                        coordinate ab(i,j);
                        auto tilez = fullboard[i]->at(j);
                        if (tilez->piece == white)
                        {
                            w++;
                        } else
                        {
                            if (tilez->piece == black) {
                                b++;
                            }
                        }
                    }
                }
                if (w > b)
                {
                    winner = white;
                }
                else if (b > w) {
                    winner = black;
                }
                else {
                    winner = tie;
                }
            }
        }
        return true;
    }
    // else
    return false;
}
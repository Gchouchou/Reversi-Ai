#include "board.h"
#define NDEBUG
#include <algorithm>
#include <assert.h>

using namespace reversi;

namespace reversi {
    struct compMoveptr {
        compMoveptr(const move &m):m(m){}
        bool operator()(const move *n) const {
            return *m.getposition() == *n->getposition();
        }
        private:
        const move &m;
    };
}

void board::placePiece(const coordinate &pos, const occupant piece) {
    tile *t = fullboard[pos.x]->at(pos.y);
    // make sure there is no piece and that it's a legit piece
    assert(t->piece == empty && isOccupied(piece));

    // then we set the piece
    t->piece = piece;
    // create a new information
    tile::info *inform = new tile::info(pos);

    // first scan for the nearby pieces
    for (int i = 0; i < 8; i++)
    {
        // go in every direction...
        direction dir = dirs[i];
        // copy the position
        coordinate coord = pos;
        // check if it is vacant and valid
        if (coord.shift(dir)) {
            if (fullboard[coord.x]->at(coord.y)->piece == empty) {
                // say there's one more free space
                ++inform->freeSpaces;
                // record it, flip direction so that we know where to move
                inform->adjEmptyTiles.push_front(new move(coord,flip(dir)));
            }
            // we now check if it's occupied
            if (isOccupied(fullboard[coord.x]->at(coord.y)->piece))
            {
                // remove this spot from it, if it's the last eye, remove info
                tile *dummy = fullboard[coord.x]->at(coord.y);
                auto bit = dummy->inf->adjEmptyTiles.before_begin();
                auto it = dummy->inf->adjEmptyTiles.begin();
                // we do it like this so we will crash if there's a bug
                while (true)
                {
                    if ((*it)->position == pos)
                    {
                        // found the invalidated move
                        // delete from memory and from the list
                        delete(*it);
                        dummy->inf->adjEmptyTiles.erase_after(bit);
                        dummy->inf->freeSpaces--;
                        break;
                    }
                    ++bit,++it;
                }
                // check if it still has worthwhile info
                if (dummy->inf->freeSpaces == 0)
                {
                    // does not, delete information
                    delete(dummy->inf);
                    dummy->inf = nullptr;
                    // remove it from the black/white tiles
                    tileList *bwList = getList(dummy->piece);
                    auto bi = bwList->before_begin();
                    auto i = bwList->begin();
                    // again, forcing it to crash if there's a bug
                    while (true)
                    {
                        if ((*i) == dummy)
                        {
                            bwList->erase_after(bi);
                            break;
                        }
                        ++i,++bi;
                    }
                }
            }
        }
    }

    // make sure we actually have relevant information
    if (inform->freeSpaces != 0)
    {
        t->inf = inform;
        getList(piece)->push_front(t);
    }
    else
    {
        delete(inform);
    }
}

void board::findValidMoves() {
    // get the list of tiles from opposing side
    tileList *l = getList(flip(who));
    // clear list
    clearValidMoves();
    cvmoves = 0;


    // for every enemy piece...
    for (auto &&t : *l)
    {
        // find every possible move...
        for (auto &&m : t->inf->adjEmptyTiles)
        {
            // determine its relative position...already did
            
            // if it is not already valid
            auto vmove = find_if(validMoves.begin(),validMoves.end(),compMoveptr(*m));
            if (vmove != validMoves.end())
            {
                // make sure it has a list
                if ((*vmove)->directions == nullptr)
                {
                    (*vmove)->directions = new move::dirList();
                }
                // it is already valid, we add a direction
                (*vmove)->directions->push_front(m->mainDir);
            }
            else
            {
                if (checkDirection(m->position,m->mainDir,who))
                {
                    auto validMove = new move(*m);
                    validMoves.push_front(validMove);
                    cvmoves++;
                }
            }
        }
    }
}

bool board::checkDirection(const coordinate &start, const direction dir, const occupant player) {
    coordinate c = start;
    // first shift by one
    if (c.shift(dir) && fullboard[c.x]->at(c.y)->piece == flip(player)) {
        while (c.shift(dir)) {
            // we check what is on this piece
            occupant pieceColor = fullboard[c.x]->at(c.y)->piece;
            // if we encounter unoccupied space we failed
            if (!isOccupied(pieceColor))
            {
                return false;
            }
            // if we encounter our own piece we good
            if (pieceColor == player)
            {
                return true;
            }
        }
    }
    // if we reach out of bounds
    return false;
}

void board::clearValidMoves() {
    clearList<move>(validMoves);
}

void board::flipTiles(const coordinate &start, const direction dir, const occupant player) {
    // dummy coordinate
    coordinate c = start;
    assert(isOccupied(player));

    while (c.shift(dir))
    {
        // get the tile
        tile *t = fullboard[c.x]->at(c.y);
        // when we reach our own piece we stop
        if (t->piece == player)
        {
            break;
        }
        // flips it otherwise
        t->flipOccupant();
        auto old = getList(flip(player));
        auto newt = getList(player);
        auto bit = old->before_begin(), it = old->begin();
        while (it != old->end())
        {
            if ((*it) == t)
            {
                newt->push_front(t);
                old->erase_after(bit);
                break;
            }
            ++bit,++it;
        }
    }
}


void board::setGameEnd() {
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
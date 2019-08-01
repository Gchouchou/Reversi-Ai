#include "board.h"

#include <algorithm>
#include <assert.h>

using namespace reversi;

void board::placePiece(const coordinate &pos, const occupant piece) {
    tile *t = fullboard[pos.x]->at(pos.y);
    // make sure there is no piece and that it's a legit piece
    assert(t->piece == empty && isOccupied(piece));
    coordinate coord;
    direction dir;

    // then we set the piece
    t->piece = piece;
    // less space left
    turnsLeft--;
    // create a new information
    info *inform = new info(pos);

    // first scan for the nearby pieces
    for (int i = 0; i < 8; i++)
    {
        // go in every direction...
        dir = dirs[i];
        // copy the position
        coord = pos;
        // check if it is vacant and valid
        if (coord.shift(dir) && fullboard[coord.x]->at(coord.y)->piece == empty) {
            // say there's one more free space
            ++inform->freeSpaces;
            // record it, flip direction so that we know where to move
            inform->adjEmptyTiles.push_front(new move(coord,flip(dir)));
        }
        else
        {
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

board::tileList *board::getList(const occupant color) {
    assert(isOccupied(color));
    if (color == white)
    {
        return &whiteEdgeTiles;
    }
    else 
    {
        return &blackEdgeTiles;
    }
}

void board::findValidMoves() {
    // get the list of tiles from opposing side
    tileList *l = getList(flip(who));
    // clear list
    clearValidMoves();

    // dummy
    move *validMove;

    // for every enemy piece...
    for (auto &&t : *l)
    {
        // find every possible move...
        for (auto &&m : t->inf->adjEmptyTiles)
        {
            // determine its relative position...already did
            
            // if it is not already valid
            auto vmove = find(validMoves.begin(),validMoves.end(),m);
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
                    validMove = new move(*m);
                    validMoves.push_front(validMove);
                    break;
                }
            }
        }
    }
}

bool board::checkDirection(const coordinate &start, const direction dir, const occupant player) {
    coordinate c = start;
    occupant pieceColor;
    while (c.shift(dir)) {
        // we check what is on this piece
        pieceColor = fullboard[c.x]->at(c.y)->piece;
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
    return false;
}

void board::clearValidMoves() {
    const move *ptr;
    while (!validMoves.empty()) {
        ptr = validMoves.front();
        validMoves.pop_front();
        delete(ptr);
    }
}

void board::flipTiles(const coordinate &start, const direction dir, const occupant player) {
    // dummy coordinate
    coordinate c = start;
    tile *t;
    assert(isOccupied(player));

    while (c.shift(dir))
    {
        // get the tile
        t = fullboard[c.x]->at(c.y);
        // when we reach our own piece we stop
        if (t->piece == player)
        {
            break;
        }
        // flips it otherwise
        t->flipOccupant();
    }
}
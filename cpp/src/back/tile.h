#ifndef TILE_HEADER
#define TILE_HEADER
#include "occupant.h"
#include "coordinate.h"
#include "move.h"

#include <forward_list>

namespace reversi
{
    class board;

    class tile
    {
    private:
        // only have relevant information when there's
        // a piece on it and it still has eyes
        struct info {
            typedef std::forward_list<const move*> constMoveList;
            // position of the tile
            const coordinate position;
            // a counter for number of free spaces left
            int freeSpaces;
            // move candidates
            constMoveList adjEmptyTiles;
            info(const coordinate &pos) : position(pos),freeSpaces(0) {}
            info(const tile::info &copy);
            ~info();
        };
        // keep track which piece is on it
        occupant piece;

        info *inf;
        // PRIVATE CONSTRUCTORS
        // constructor of a piece, defaults to empty
        tile():piece(empty) {inf = nullptr;}
        ~tile();
    public:
        // flips from black onto white
        void flipOccupant();
        tile(const tile &copy);

        // getter
        const occupant getPiece() const{return piece;}
    friend class board;
    };
    
} // namespace reversi


#endif
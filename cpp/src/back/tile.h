#ifndef TILE_HEADER
#define TILE_HEADER
#include "occupant.h"
#include "coordinate.h"

#include <list>

namespace reversi
{
    class board;

    class tile
    {
    private:
        // keep track which piece is on it
        occupant piece;

        // position of the tile
        coordinate position;
        // a counter for number of free spaces left
        int freeSpaces;
        std::list<const tile*> *adjEmptyTiles;
    public:
        // flips from black onto white
        void flipOccupant();
            // if (!(piece > empty)) {

            // }
            // piece = (occupant)(3 - piece);
 

        // constructor of a piece, defaults to empty
        tile(const coordinate &cord, const occupant piece = occupant::empty): \
        piece(piece), position(cord) {}
        ~tile();

    friend class board;
    };
    
} // namespace reversi


#endif
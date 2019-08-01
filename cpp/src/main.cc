#include "board.h"
#include "coordinate.h"
#include "tile.h"

#include <iostream>

using namespace reversi;
using namespace std;

int main(int argc, char const *argv[])
{
    board BEHELD;
    board BEHOLD(BEHELD);
    auto c =coordinate(2,3);
    BEHOLD.playTurn(c);
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            cout << BEHOLD.getTile(coordinate(i,j))->getPiece();
        }
        cout << "\n";
    }
    validMoveList v;
    BEHOLD.getValidMoves(v);
    for (auto &&coord : v)
    {
        cout << coord->x << "," << coord->y << "\n";
    }
    cout << flush;
    clearList<const coordinate>(v);
    return 0;
}

#include "board.h"
#include "coordinate.h"
#include "tile.h"

#include <iostream>

using namespace reversi;
using namespace std;

int main(int argc, char const *argv[])
{
    board BEHOLD;
    auto c =coordinate(0,1);
    BEHOLD.playTurn(c);
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            cout << BEHOLD.getTile(coordinate(i,j))->getPiece();
        }
        cout << "\n";
    }
    cout << flush;
    return 0;
}

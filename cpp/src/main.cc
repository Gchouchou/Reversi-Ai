#include "board.h"
#include "coordinate.h"
#include "tile.h"

#include <iostream>

using namespace reversi;
using namespace std;

int main(int argc, char const *argv[])
{
    board BEHOLD;
    auto moves = BEHOLD.getValidMoves();
    auto c =coordinate(1,1);
    for (auto &&i : *moves)
    {
        cout << i->x << "," << i->y << "\n";
    }
    cout << flush;
    for (auto &&i : *moves)
    {
        delete(i);
    }
    delete(moves);
    return 0;
}

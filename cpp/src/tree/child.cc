#include "child.h"

#include <random>

using namespace reversi;

namespace 
{
    const coordinate *selectRand(validMoveList &l) {
        std::uniform_int_distribution<int> gen(0,l.size()-1);
        return l[gen(*child::gen)];
    }
} // namespace 

occupant child::player = empty;
std::default_random_engine *child::gen = nullptr;

child::child(const board &rootState, const coordinate &move):win(0),total(0) {
    // get the right move
    state = new board(rootState);
    state->playTurn(move);
    origin = &move;
}

child::~child() {
    delete(origin);
}

void child::runSimulation() {
    // clone the state
    board tester(*state);
    validMoveList list;
    tester.getValidMoves(list);
    // play until the end of the game
    while (!tester.playTurn(*selectRand(list)))
    {
        tester.getValidMoves(list);
    }

    total++;
    occupant winner = tester.getWinner();
    if (winner == player)
    {
        win += 1;
    }
    else if (winner == tie)
    {
        win += 0.5;
    }
    // we lost we don't do anything
}
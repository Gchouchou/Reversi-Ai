#include "tree.h"

#include <chrono>
#include <math.h>
#include <time.h>

using namespace reversi;
using namespace MCT;

const coordinate MCT::tree::d(-1,0);
MCT::tree::tree(reversi::gui &interface, reversi::occupant player) :player(player),
interface(&interface),flag(false),bestMove(&d),done(true),total(0) {
    // current board
    root = new board(interface.getBoard());
    // setup the static variables
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen = new std::default_random_engine(seed);
    node::gen = gen;
    treeRoot = new node(*root);
}

tree::~tree() {
    flag = false;
    while (!done)
    ;
    delete(root);
    delete(treeRoot);
    if (bestMove != &d)
    {
        delete(bestMove);
    }
    delete(gen);
}


void tree::chooseChild(coordinate &c) {
    // wait until it's back down
    while (flag && !done)
    ;
    root->playTurn(c);
    // move down
    auto d =treeRoot->moveDown(c,*root);
    delete(treeRoot);
    // also update root
    treeRoot = d;
}

void tree::startSearching() {
    while (flag && !done)
    ;
    done = false;
    flag = true;
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC,&start);
    do
    {
        auto dummy = (new board(*root));
        treeRoot->search(*dummy);
        delete(dummy);
        // we only update/show when it's on our turn
        if (root->getWho() == player)
        {
            auto moves = treeRoot->selectBestNode();
            if (bestMove != moves)
            {
                bestMove = moves;
                interface->updatesuggested(*bestMove);
                interface->updateWin(false);
            }
        }
        clock_gettime(CLOCK_MONOTONIC,&finish);
    } while (flag && (finish.tv_sec- start.tv_sec) < 10);
    // we are done so we just wait
    bestMove = &d;
    interface->updatesuggested(*bestMove);
    done = true;
}
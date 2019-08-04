#include "tree.h"
#include "interface.h"

#include <chrono>
#include <math.h>

using namespace reversi;

namespace
{
    inline double formula(double win, double sub,unsigned int total) {
        return (win /sub) + CONSTANT*(sqrt(log(total)/sub));
    }
} // namespace


const coordinate tree::d(-1,0);

tree::tree(gui &interface, const occupant player):player(player),
interface(&interface),flag(false),bestMove(&d),done(true),total(0) {
    // current board
    root = new board(interface.currBoard);
    // setup the static variables
    child::player = player;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen = new std::default_random_engine(seed);
    child::gen = gen;
    // populate the children
    validMoveList l;
    root->getValidMoves(l);
    for (auto &&m : l)
    {
        children.push_back(new child(*root,*m));
    }
}

tree::~tree() {
    while (flag && !done)
    ;
    // clear the child nodes
    while (!children.empty())
    {
        delete(children.back()->state);
        delete(children.back());
        children.pop_back();
    }
    delete(root);
    delete(bestMove);
    delete(gen);
}


void tree::chooseChild(coordinate &c) {
    // wait until it's back down
    while (flag && !done)
    ;
    // select the right child and delete all the rest
    while (!children.empty())
    {
        if (*children.back()->origin == c)
        {
            delete(root);
            root = children.back()->state;
        } else
        {
            delete(children.back()->state);
        }
        delete(children.back());
        children.pop_back();
    }
    // populate the children
    validMoveList l;
    root->getValidMoves(l);
    for (auto &&m : l)
    {
        children.push_back(new child(*root,*m));
    }
}

void tree::startSearching() {
    while (flag && !done)
    ;
    done = false;
    flag = true;
    // first run a simulation on every node
    for (auto &&c : children)
    {
        total++;
        c->runSimulation();
    }
    while (flag)
    {
        // selecting the best
        std::vector<child *> best;
        double bestS = -1;
        for (auto &&c : children)
        {
            double scror = formula(c->win,c->total,total);
            if (scror > bestS)
            {
                bestS = scror;
                best.clear();
                best.push_back(c);
            }
            else if (scror == bestS)
            {
                best.push_back(c);
            }
        }
        // choose a random child to *expand search
        std::uniform_int_distribution<int> generator(0,best.size()-1);
        child *searched = best[generator(*gen)];
        searched->runSimulation();
        total++;
        // now we check which one was the most valuable
        best.clear();
        bestS = 0;
        for (auto &&c : children)
        {
            if (c->total > bestS)
            {
                bestS = c->total;
                best.clear();
                best.push_back(c);
            }
            else if (c->total == bestS)
            {
                best.push_back(c);
            }
        }
        std::uniform_int_distribution<int> generator2(0,best.size()-1);
        // do a check to save the frames
        auto buff = best[generator2(*gen)]->origin;
        if (bestMove != buff && flag) {
            bestMove = buff;
            interface->updatesuggested(*bestMove);
            interface->updateWin(false);
        }
    }
    bestMove = &d;
    interface->updatesuggested(*bestMove);
    done = true;
}
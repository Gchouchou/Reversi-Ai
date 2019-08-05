#include "node.h"

using namespace MCT;
using namespace reversi;

typedef std::vector<node*> nodeList;

std::default_random_engine *node::gen = nullptr;
unsigned node::count = 0;

namespace 
{
    inline node *getRandomNode(const nodeList &list) {
        std::uniform_int_distribution<int> ab(0,list.size()-1);
        return list[ab(*node::gen)];
    }
    inline double formula(double win, double sub,unsigned int total) {
        return (win /sub) + 1.5*(sqrt(log(total)/sub));
    }
} // namespace 

node::node(reversi::board &state):wins(0),total(0),who(state.getWho()) {
    count++;
    createChildren(state);
}

void node::createChildren(reversi::board &state) {
    children = new nodeList();
    validMoveList l;
    state.getValidMoves(l);
    for (auto &&m : l)
    {
        // have to make simulated runs reee
        reversi::board b(state);
        b.playTurn(*m);
        children->push_back(new node(*m,b.getWho()));
    }
    clearList(l);
    // save the space
    children->shrink_to_fit();
}

node::~node() {
    count--;
    if (children != nullptr)
    {
        while (!children->empty())
        {
            delete(children->back());
            children->pop_back();
        }
        delete(children);
        children = nullptr;
    }
}

node* node::moveDown(reversi::coordinate &move,reversi::board &root) {
    node *rvaluea;
    while (!children->empty())
    {
        auto nptr = children->back();
        if (nptr->origin == move)
        {
            rvaluea = nptr;
        } else
        {
            delete(nptr);
        }
        children->pop_back();
    }
    delete(children);
    children = nullptr;
    if (rvaluea->children == nullptr)
    {
        rvaluea->createChildren(root);
    }
    return rvaluea;
}


reversi::coordinate *node::selectBestNode() {
    unsigned max(0);
    nodeList bests;
    for (auto &&n : *children)
    {
        if (max < n->total)
        {
            max = n->total;
            bests.clear();
            bests.push_back(n);
        } else if (max == n->total) {
            bests.push_back(n);
        }
    }
    return &getRandomNode(bests)->origin;
}

reversi::occupant node::search(reversi::board &state) {
    auto child = selection();
    state.playTurn(child->origin);
    occupant result;
    if (child->total != 0)
    {
        // recursive call
        result = child->search(state);
    } else {
        // do a playout
        result = child->playout(state);
    }
    if (result == who)
    {
        wins++;
    }
    else if (result == tie) {
        wins += 0.5;
    }
    total++;
    return result;
}

node *node::selection() {
    nodeList bests;
    double bestScore(-1.0);
    for (auto &&c : *children)
    {
        double scror;
        if (c->total != 0)
        {
            if (c->who == this->who)
            {
                scror = formula(c->total - c->wins,c->total,this->total);
            }
            else
            {
                scror = formula(c->wins,c->total,this->total);
            }
        } else
        {
            scror = 200000000000.0;
        }
        if (scror > bestScore)
        {
            bestScore = scror;
            bests.clear();
            bests.push_back(c);
        } else if (scror == bestScore) {
            bests.push_back(c);
        }
    }
    return getRandomNode(bests);
}


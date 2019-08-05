#ifndef NODE_HEADER
#define NODE_HEADER
#include "occupant.h"
#include "coordinate.h"
#include "board.h"

#include <vector>
#include <random>

#define MAX_NODES 100000

namespace MCT
{
    class node
    {
    private:
        // not initiated at the beginning
        std::vector<node*> *children;
        double wins;
        unsigned total;
        // game specifics
        reversi::occupant who;
        reversi::coordinate origin;
        // max nodes
        static unsigned count;

        /*
        does a tree search, the return value tells us who won so we can back propagate
        */
        reversi::occupant search(reversi::board &state);
        // select node according to formula
        node *selection();
        // play it out, return winner, populates children list
        reversi::occupant playout(reversi::board &state);
        // populates the children list
        void createChildren(reversi::board &state);
        // created from node
        node(const reversi::coordinate &vmove, reversi::occupant who):
        wins(0),total(0),who(who),origin(vmove){children = nullptr;count++;}
    public:
        // static random
        static std::default_random_engine *gen;
        // select the coord that has the most visits
        reversi::coordinate *selectBestNode();
        // move down the tree, return the new root
        node* moveDown(reversi::coordinate &move,reversi::board &root);

        // create from an initial board state, creates all the children
        node(reversi::board &state);
        // recursively delete every node
        ~node();
        friend class tree;
    };
} // namespace MCT



#endif

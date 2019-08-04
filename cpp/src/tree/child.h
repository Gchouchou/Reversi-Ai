#ifndef CHILD_HEADER
#define CHILD_HEADER
#include "board.h"
#include "coordinate.h"

#include <random>

namespace reversi
{
    class child
    {
    private:
        typedef unsigned int count;
        // organized by tree
        board *state;
        // not organized by tree
        const coordinate *origin;
        double win;
        count total;
        static occupant player;
    public:
        static std::default_random_engine *gen;
        void runSimulation();
        // created from a root node
        child(const board &rootState, const coordinate &move);
        ~child();
    friend class tree;
    };
} // namespace reversi


#endif
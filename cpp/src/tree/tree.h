#ifndef TREE_HEADER
#define TREE_HEADER
#include "board.h"
#include "node.h"
#include "occupant.h"
#include "interface.h"

#include <vector>
#include <mutex>
#include <random>

#define CONSTANT 1

namespace reversi {
    class gui;
}

namespace MCT {
    // very basic implementation of tree search
    class tree
    {
    private:
        reversi::board *root;
        node *treeRoot;
        const reversi::coordinate *bestMove;
        unsigned int total;
        // thread terminated
        bool done;
        // to signal
        reversi::gui *interface;
        // lock
        std::mutex mutex;
        std::default_random_engine *gen;
        reversi::occupant player;
        static const reversi::coordinate d;

        // update best move
        void updateBest();
    public:
        // controls when we stop searching
        bool flag;

        void setFlag() {
            mutex.lock();
            flag = false;
            mutex.unlock();
        }
        bool doneSearch() {
            mutex.lock();
            bool a = !flag && done;
            mutex.unlock();
            return a;
        }
        void startSearching();
        void chooseChild(reversi::coordinate &c);
        reversi::occupant getPlayer() {return player;}
        tree(reversi::gui &interface, const reversi::occupant player);
        ~tree();
    };
}

#endif

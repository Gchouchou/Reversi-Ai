#ifndef TREE_HEADER
#define TREE_HEADER
#include "child.h"
#include "board.h"

#include <vector>
#include <mutex>
#include <random>

#define CONSTANT 1

namespace reversi {
    class gui;
    // very basic implementation of tree search
    class tree
    {
    private:
        board *root;
        const coordinate *bestMove;
        std::vector<child*> children;
        unsigned int total;
        // thread terminated
        bool done;
        // to signal
        gui *interface;
        // lock
        std::mutex mutex;
        std::default_random_engine *gen;
        occupant player;
        static const coordinate d;

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
        void chooseChild(coordinate &c);
        occupant getPlayer() {return player;}
        tree(gui &interface, const occupant player);
        ~tree();
        friend class gui;
    };
}

#endif

#include "node.h"

using namespace MCT;
using namespace reversi;

typedef std::vector<node*> nodeList;

namespace 
{
    const int selectIndex(const std::vector<int> &vector) {
        unsigned total(0);
        for (auto &&i : vector)
        {
            total += i;
        }
        // got the total
        double ratioTotal(0);
        std::vector<double> ratios;
        for (size_t i = 0; i < vector.size(); i++)
        {
            double a =vector[i];
            if (a == 0)
            {
                a = 0.5;
            }
            auto d = ( (double) total )/ a;
            ratioTotal += d;
            ratios.push_back(d);
        }
        std::uniform_real_distribution<double> gen(0,ratioTotal);
        double result = gen(*node::gen);
        ratioTotal = 0;
        for (int i = 0; i < ratios.size(); i++)
        {
            ratioTotal += ratios[i];
            if (result <= ratioTotal)
            {
                return i;
            }
        }
    }
} // namespace


reversi::occupant node::playout(reversi::board &state) {
    // if we exceed max count we do not initialize children
    // if (count < MAX_NODES)
    createChildren(state);
    // now we play until the end
    validMoveList vlist;
    while(state.getWinner() == empty) {
        state.getValidMoves(vlist);
        occupant current = state.getWho();
        std::vector<int> indexes;
        for (size_t i = 0; i < vlist.size(); i++)
        {
            auto s = new board(state);
            if (!s->playTurn(*vlist[i])) {
                if (s->getWho() == current)
                {
                    // we have a double move probably should choose this
                    indexes.push_back(0);
                } else
                {
                    // just add the size to the index
                    indexes.push_back(s->eval());
                }
            } else
            {
                // game end (future)
                occupant winner = s->getWinner();
                if (winner == current)
                {
                    // this is the end
                    clearList(vlist);
                    delete(s);
                    return winner;
                } else if (winner == flip(current)) {
                    // highest number possible
                    indexes.push_back(10000);
                } else
                {
                    // tis a tie just a decent number
                    indexes.push_back(20);
                }
            }
            delete(s);
        }
        if (state.playTurn(*vlist[selectIndex(indexes)]))
        {
            // the game is over
            clearList(vlist);
            break;
        }
    }

    // update score only if we have enough space
    if (children != nullptr)
    {
        total++;
        if (state.getWinner() == who)
        {
            wins++;
        }
        else if (state.getWinner() == tie) {
            wins += 0.5;
        }
    }
    return state.getWinner();
}

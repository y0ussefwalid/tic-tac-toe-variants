#include "BoardGame_Classes.h"

#ifndef MINMAX_TESTING_MISEREAI_H
#define MINMAX_TESTING_MISEREAI_H
template<typename T>
class misereAI : public Player<T>{
public:
    misereAI(string name,T symbol);
    void getmove(int& x, int& y) override;
    int minmax(T symbol,bool maximize);
};
//--------------------------------------- IMPLEMENTATION
#include <limits>
template<typename T>
misereAI<T>::misereAI(std::string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void misereAI<T>::getmove(int& x, int& y) {
    int bestScore = std::numeric_limits<int>::min(); // Minimize score for Misère
    int bestX = -1, bestY = -1;
    char op = (this->symbol == 'X') ? 'O' : 'X';
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i+1,j+1,this->symbol)) {
                int score = minmax(op, false);
                this->boardPtr->update_board(i+1,j+1,0);
                if (score > bestScore) {
                    bestScore = score;
                    bestX = i;
                    bestY = j;
                }
            }
        }
    }

    x = bestX+1;
    y = bestY+1;
}
template<typename T>
int misereAI<T>::minmax(T symbol, bool maximize) {
    if (this->boardPtr->is_win()) return maximize ? 1 : -1;
    if (this->boardPtr->is_draw()) return 0;

    char op = (symbol == 'X') ? 'O' : 'X';
    int bestScore = maximize ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j){
            if (this->boardPtr->update_board(i+1, j+1, symbol)) {
                    int score = minmax(op, !maximize);
                    this->boardPtr->update_board(i+1, j+1, 0); // Undo move
                    bestScore = maximize ? std::max(bestScore, score) : std::min(bestScore, score);
            }
        }
    }
    return bestScore;
}



#endif //MINMAX_TESTING_MISEREAI_H

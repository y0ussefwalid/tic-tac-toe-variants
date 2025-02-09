#pragma once
#include "BoardGame_Classes.h"
#include <set>
template<typename T>
class _5x5_board : public Board<T>  {

private:
    set<int>counted;
    Player<T>* playerptr[2];
    int wins1;
    int wins2;
    bool& win;
    bool end;
public:

	_5x5_board(Player<T>*[2],bool&);
	bool update_board(int,int,T);
	void display_board();
	bool is_win();
	bool is_draw();
	bool game_is_over();
    void show_score();
    ~_5x5_board();
};
template<typename T>
class _5x5_player : public Player<T>{
private:
    bool& win;
public:
	_5x5_player(string, T,bool&);
	void getmove(int&, int&);
};
template<typename T>
class _5x5_Random : public RandomPlayer<T> {
private:
    bool& win;
public:
	_5x5_Random(T,bool&);
	void getmove(int&, int&);
};


//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>

template<typename T>
_5x5_board<T>::_5x5_board(Player<T>* pptr[2],bool& w) : win(w) , end(false) {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < 5; ++i) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < 5; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    this->wins1 = this->wins2 = 0;
    this->playerptr[0] = pptr[0];
    this->playerptr[1] = pptr[1];
}
template<typename T>
bool _5x5_board<T>::update_board(int x, int y, T symbol) {
    if(this->win) return true;
    else if ((x == y) && x == -1) {
        this->end = true;
        return true;
    }
    --x;--y;
	if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
		this->board[x][y] = toupper(symbol);
		this->n_moves++;
	}
    else return false;
	return true;
}


template<typename T>
bool _5x5_board<T>::is_win() {
    if(this->win){
        this->show_score();
        return true;
    }else if(this->end) return false;
    // Check all possible 3x3 subgrids in the 5x5 board
    //create a set for indices that are already taken
    for (int startRow = 0; startRow <= 2; ++startRow) {
        for (int startCol = 0; startCol <= 2; ++startCol) {
            // Check rows and columns within the current 3x3 subgrid
            for (int i = 0; i < 3; ++i) {
                // Row check
                if (this->board[startRow + i][startCol] != 0 &&
                    this->board[startRow + i][startCol] == this->board[startRow + i][startCol + 1] &&
                    this->board[startRow + i][startCol + 1] == this->board[startRow + i][startCol + 2]) {
                    int loc = (startRow+i)*100000;
                    loc += startCol*10000;
                    loc+= (startRow+i)*1000;
                    loc+= (startCol+1)*100;
                    loc+= (startRow+i)*10;
                    loc+= (startCol+2);
                    if(!counted.count(loc)) {
                        counted.insert(loc);
                        if (this->board[startRow + i][startCol] == 'X')this->wins1++;
                        else this->wins2++;
                    }
                }

                // Column check
                if (this->board[startRow][startCol + i] != 0 &&
                    this->board[startRow][startCol + i] == this->board[startRow + 1][startCol + i] &&
                    this->board[startRow + 1][startCol + i] == this->board[startRow + 2][startCol + i]) {
                    int loc = startRow * 100000;
                    loc += (startCol + i) * 10000;
                    loc += (startRow + 1) * 1000;
                    loc += (startCol + i) * 100;
                    loc += (startRow + 2) * 10;
                    loc += (startCol + i);
                    if (!counted.count(loc)) {
                        counted.insert(loc);
                        if (this->board[startRow][startCol + i] == 'X') this->wins1++;
                        else this->wins2++;
                    }
                }

            }

            // First diagonal check (\ direction)
            if (this->board[startRow][startCol] != 0 &&
                this->board[startRow][startCol] == this->board[startRow + 1][startCol + 1] &&
                this->board[startRow + 1][startCol + 1] == this->board[startRow + 2][startCol + 2]) {
                int loc = startRow * 100000;
                loc += startCol * 10000;
                loc += (startRow + 1) * 1000;
                loc += (startCol + 1) * 100;
                loc += (startRow + 2) * 10;
                loc += (startCol + 2);
                if (!counted.count(loc)) {
                    counted.insert(loc);
                    if (this->board[startRow][startCol] == 'X') this->wins1++;
                    else this->wins2++;
                }
            }

                // Second diagonal check (/ direction)
            if (this->board[startRow][startCol + 2] != 0 &&
                this->board[startRow][startCol + 2] == this->board[startRow + 1][startCol + 1] &&
                this->board[startRow + 1][startCol + 1] == this->board[startRow + 2][startCol]) {
                int loc = startRow * 100000;
                loc += (startCol + 2) * 10000;
                loc += (startRow + 1) * 1000;
                loc += (startCol + 1) * 100;
                loc += (startRow + 2) * 10;
                loc += startCol;
                if (!counted.count(loc)) {
                    counted.insert(loc);
                    if (this->board[startRow][startCol + 2] == 'X') this->wins1++;
                    else this->wins2++;
                }
            }

        }
    }
    this->show_score();
    // Check if the game should end
    if (this->n_moves == 24) {
        if (this->wins1 > this->wins2) {
            this->win = true;
        } else if (this->wins1 < this->wins2) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool _5x5_board<T>::is_draw(){
	return (this->n_moves == 24 && this->wins1 == this->wins2);
}
template<typename T>
bool _5x5_board<T>::game_is_over() {
	return(this->n_moves == 25 || this->end);
}
template<typename T>
void _5x5_board<T>::display_board() {
    cout << "   ";
	for (int i = 0; i < this->columns; ++i) {
		cout << setw(2) << left << i + 1 << '|';
	}
    cout <<"\n   " << string(15,'-') << '\n';
	for (int i = 0; i < this->rows; ++i) {
        cout << setw(2) << left << i + 1 << '|';
		for (int j = 0; j < this->columns; ++j) {
			if(this->board[i][j] !=0) cout << setw(2) << left << this->board[i][j] << '|';
            else cout << "  |";
		}
		cout << '\n';
        cout <<"   " <<string(15,'-') << '\n';
	}
}
template<typename T>
void _5x5_board<T>::show_score() {
    cout << " ======================\n";
    cout << "|      SCOREBOARD      |\n";
    cout << " ======================\n";
    cout << "| Player               | Wins |\n";
    cout << " ----------------------|------|\n";
    cout << "| " << left << setw(20) << playerptr[0]->getname() << " | " << right << setw(4) << wins1 << " |\n";
    cout << "| " << left << setw(20) << playerptr[1]->getname() << " | " << right << setw(4) << wins2 << " |\n";
    cout << " ======================\n";
}

template<typename T>
_5x5_board<T>::~_5x5_board() {
    for (int i = 0; i < this->rows; ++i) {
        delete [] this->board[i];
    }
    delete [] this->board;
}
//----------------------------------------------
template <typename T>
_5x5_player<T>::_5x5_player(string name, T symbol,bool& w) : Player<T>(name, symbol),win(w){}
template<typename T>
void _5x5_player<T>::getmove(int& x, int& y){
    if(this->win) return;
    else if(this->boardPtr->game_is_over()) return;
    string choice;
    while (choice.size() != 3 || !isdigit(choice[0]) || !isdigit(choice[2]) || isdigit(choice[1])) {
        cout << "enter 'return' to return to menu\n";
        cout << "Enter your move as two numbers \"row column\", separated by a space: ";
        getline(cin, choice);
        cout << "\x1b[1A";
        cout << "\x1b[K";
        cout << "\x1b[1A";
        cout << "\x1b[K";
        if(choice == "return"){
            x = -1;
            y = -1;
            return;
        }
    }
    x = static_cast<int>(choice[0]) - '0';
    y = static_cast<int>(choice[2]) - '0';
}
//---------------------------------------------
template<typename T>
_5x5_Random<T>::_5x5_Random(T symbol,bool& w) : RandomPlayer<T>(symbol),win(w) {
    this->dimension = 5;
	srand(time(NULL));
}
template<typename T>
void _5x5_Random<T>::getmove(int& x, int& y) {
    if(this->win) return;
    else if(this->boardPtr->game_is_over())return;
    x = rand() % this->dimension;
	y = rand() % this->dimension;
}

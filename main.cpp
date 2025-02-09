#include <iostream>
#include <string>
#include "5x5X_O.h"
#include "misere.h"
#include "misereAI.h"

void getNameAndType(std::string& player1, std::string& player2, int& type1 , int& type2) {
    std::string type1String, type2String;
    std::cout << "Choose Player 1 Name: ";
    std::cin >> player1;

    do {
        std::cout << "Choose Player 1 type: \n";
        std::cout << "1. Human\n";
        std::cout << "2. Random Computer\n";
        std::cout << "3. AI\n";
        std::getline(std::cin >> std::ws, type1String);
    } while(type1String.length() > 1 || type1String[0] > '3' || type1String[0] < '1');
    type1 = type1String[0] - '0';

    std::cout << "Choose Player 2 Name: ";
    std::cin >> player2;

    do {
        std::cout << "Choose Player 2 type: \n";
        std::cout << "1. Human\n";
        std::cout << "2. Random Computer\n";
        std::cout << "3. AI\n";
        std::getline(std::cin >> std::ws, type2String);
    } while(type2String.length() > 1 || type2String[0] > '3' || type2String[0] < '1');
    type2 = type2String[0] - '0';
}

void misere() {
    Player<char>* players[2];
    Board<char>* B = new misere_board<char>();
    std::string player1Name, player2Name;
    int type1, type2;
    getNameAndType(player2Name, player1Name, type1, type2);
    switch(type1) {
        case 1:
            players[0] = new misere_Player<char>(player1Name, 'X', B);
            break;
        case 2:
            players[0] = new misere_Random_Player<char>(player1Name, 'X', B);
            break;
        case 3:
            players[0] = new misereAI<char>(player1Name, 'X');
            players[0]->setBoard(B);
            break;
        default:
            std::cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }
    switch(type2) {
        case 1:
            players[1] = new misere_Player<char>(player2Name, 'O', B);
            break;
        case 2:
            players[1] = new misere_Random_Player<char>(player2Name, 'O', B);
            break;
        case 3:
            players[1] = new misereAI<char>(player2Name, 'O');
            players[1]->setBoard(B);
            break;
        default:
            std::cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }
    GameManager<char> x_o_game(B, players);
    x_o_game.run();
    delete B;
    for (auto & player : players) {
        delete player;
    }
}

void _5x5(){
    bool win = false;
    Player<char>* players[2];
    string player1Name, player2Name;
    int type1, type2;
    std::cout << "----------------------------\n";
    std::cout << "|    Welcome to 5x5 XO     |\n";
    std::cout << "----------------------------\n";
    getNameAndType(player1Name,player2Name, type1, type2);
    switch (type1) {
        case 1:
            players[0] = new _5x5_player<char>(player1Name, 'X',win);
            break;
        case 2:
            players[0] = new _5x5_Random<char>('X',win);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }
    switch (type2) {
        case 1:
            players[1] = new _5x5_player<char>(player2Name, '0',win);
            break;
        case 2:
            players[1] = new _5x5_Random<char>('0',win);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }
    Board<char>* B = new _5x5_board<char>(players,win);
    players[0]->setBoard(B);
    players[1]->setBoard(B);
    GameManager<char> game(B, players);
    game.run();
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

int main() {
    std::cout << "-------------------------\n";
    std::cout << "| Welcome to Mini Games |\n";
    std::cout << "-------------------------\n";
    std::string choiceString;
    int choice;
    while (true) {
        std::cout << "Choose one of the following games to start playing or exit the program\n";
        std::cout << "1. 5x5 Tic Tac Toe\n";
        std::cout << "2. Misere Tic Tac Toe\n";
        std::cout << "3. Exit\n";
        while (true) {
            std::cout << "Enter Your choice: ";
            std::getline(std::cin >> std::ws, choiceString);
            if(choiceString.length() != 1 || choiceString[0] < '1' || choiceString[0] > '3') {
                std::cout << "Invalid choice\n";
                continue;
            }
            break;
        }
        choice = choiceString[0] - '0';
        switch (choice) {
            case 1:
                _5x5();
                break;
            case 2:
                misere();
                break;
            case 3:
                return 0;
            default:
                return 0;
        }
    }
}

#include <iostream>
#include <limits>
#include "board.cc"
#include "ship.cc"
#include "player.cc"
#include <thread>
#include <chrono>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void displayBoards(Player& player1, Player& player2, int currentPlayer) {
    if (currentPlayer == 1) {
        cout << "Your board:" << endl;
        player1.getBoard().showBoard();
        cout << "\nOpponent's board:" << endl;
        player2.getBoard().showHiddenBoard();
    } else {
        cout << "Your board:" << endl;
        player2.getBoard().showBoard();
        cout << "\nOpponent's board:" << endl;
        player1.getBoard().showHiddenBoard();
    }
}

bool getPlayerShot(Player& player1, Player& player2, int currentPlayer, int& row, int& col) {
    while (true) {
        cout << "\nSet row where you want to shoot (0-9): ";
        cin >> row;
        cout << "Set column where you want to shoot (0-9): ";
        cin >> col;

        if (cin.fail() || row < 0 || row >= 10 || col < 0 || col >= 10) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid coordinates! Please try again." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            clearScreen();
            displayBoards(player1, player2, currentPlayer);
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }
    }
}

int main()
{
    Player player1;
    Player player2;

    clearScreen();
    cout << "Player 1, set your nickname: ";
    player1.setPlayerName();
    clearScreen();
    cout << "Player 2, set your nickname: ";
    player2.setPlayerName();
    clearScreen();

    bool playAgain = true;

    while(playAgain)
    {
        cout << player1.getPlayerName() << ", set your ships:" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        player1.setShips();
        clearScreen();

        cout << player2.getPlayerName() << ", set your ships:" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        player2.setShips();

        bool gameOver = false;
        int currentPlayer = 1;

        while (!gameOver) {
            clearScreen();
            cout << (currentPlayer == 1 ? player1.getPlayerName() : player2.getPlayerName()) << "'s turn!" << endl;

            displayBoards(player1, player2, currentPlayer);

            int row, col;
            getPlayerShot(player1, player2, currentPlayer, row, col);

            bool hit = (currentPlayer == 1) ? player2.getBoard().shoot(row, col) : player1.getBoard().shoot(row, col);

            clearScreen();
            cout << (hit ? "Hit!" : "Miss!") << endl;
            if (hit) {
                if ((currentPlayer == 1 && player2.getBoard().isGameOver()) || (currentPlayer == 2 && player1.getBoard().isGameOver())) {
                    cout << (currentPlayer == 1 ? player1.getPlayerName() : player2.getPlayerName()) << " wins!" << endl;
                    if (currentPlayer == 1) {
                        player1.addPlayerWin();
                    } else {
                        player2.addPlayerWin();
                    }
                    gameOver = true;
                }
            } else {
                cout << "Press any key to change player..." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                currentPlayer = (currentPlayer == 1) ? 2 : 1;

            }

            if (!gameOver) {
                this_thread::sleep_for(chrono::seconds(1));
            }
        }

        cout << "Game over!" << endl;
        cout << "Final score:\n";
        cout << player1.getPlayerName() << ": " << player1.getPlayerWins() << " wins\n";
        cout << player2.getPlayerName() << ": " << player2.getPlayerWins() << " wins\n";

        char choice;
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            player1.getBoard().resetBoard();
            player2.getBoard().resetBoard();
            playAgain = true;
        } else {
            playAgain = false;
        }
    }
    cout << "Thanks for playing! I hope you had fun!" << endl;
}

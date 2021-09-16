//! Author: Arindam

#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <set>

#define BOARD_SIZE 3

class Game{
private:
    bool isEnd;
    int player_turn;
    std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE> board;

    // Reset the Board
    void reset () {
        player_turn = 1;
        isEnd = false;
        for (auto& i : board)
            i.fill(0);
    }

    // Returns set of all the available positions
    std::set<std::pair<int, int>> available_positions() {
        std::set<std::pair<int, int>> a;

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == 0)
                    a.insert({i, j});
            }
        }

        return a;
    }

    // Check for Winner
    int check_winner() {
        // For Rows
        for (int i = 0; i < BOARD_SIZE; i++) {
            int sum = 0;
            for (int j = 0; j < BOARD_SIZE; j++) {
                sum += board[i][j];
            }

            if (abs(sum) == BOARD_SIZE) {
                isEnd = true;
                return sum/BOARD_SIZE;
            }
        }

        // For column
        for (int i = 0; i < BOARD_SIZE; i++) {
            int sum = 0;
            for (int j = 0; j < BOARD_SIZE; j++) {
                sum += board[j][i];
            }

            if (abs(sum) == BOARD_SIZE) {
                isEnd = true;
                return sum/BOARD_SIZE;
            }
        }

        // For Diagonal
        int dia1 = 0, dia2 = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (i == j)
                    dia1 += board[i][j];
                if (i == BOARD_SIZE - j - 1)
                    dia2 += board[i][BOARD_SIZE - i - 1];
            }
        }

        if (abs(dia1) == BOARD_SIZE || abs(dia2) == BOARD_SIZE) {
            isEnd = true;
            return abs(dia1) == BOARD_SIZE ?
                    dia1 / BOARD_SIZE :
                    dia2 / BOARD_SIZE;
        }

        // For Checking Draw Games
        if (available_positions().empty()) {
            isEnd = true;
            return 0;
        }

        return 0;
    }

    // Input Pattern for Human understanding :)
    void show_input_pattern() {
        std::cout << "Choose the position below ...." << '\n';
        for (int i = 0; i < BOARD_SIZE; i++) {
            std::cout << "-------------" << '\n';
            std::cout << '|';
            for (int j = 0; j < BOARD_SIZE; j++) {
                std::cout <<  ' ' << (BOARD_SIZE * i + j) << ' ';
                std::cout << '|';
            }
            std::cout << '\n';
        }
        std::cout << "-------------" << "\n\n";
    }


    // Display the board
    void show_board () {
        for (int i = 0; i < BOARD_SIZE; i++) {
            std::cout << "-------------" << '\n';
            std::cout << '|';
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == 1) {
                    std::cout << " X ";
                }
                else if (board[i][j] == -1) {
                    std::cout << " O ";
                }
                else if (board[i][j] == 0) {
                    std::cout << "   ";
                }
                std::cout << '|';
            }
            std::cout << '\n';
        }
        std::cout << "-------------" << "\n\n";
    }

    // Choose action on the board (For Human Players)
    std::pair<int, int> choose_action(std::set<std::pair<int, int>> pos) {
        int x;
        while (1) {
            std::cout << "Input your Action Position 0-8: ";
            std::cin >> x;

            std::pair action = std::make_pair(x / BOARD_SIZE, x % BOARD_SIZE);
            if (pos.find(action) != pos.end()) {
                return action;
            } else {
                std::cout << "Position out of bound OR is Preoccupied."
                     << " Try again...\n";
            }
        }
    }

    // Updates the board and next player turn
    void switch_player(std::pair<int, int> pos) {
        board[pos.first][pos.second] = player_turn;
        player_turn = player_turn == 1 ? -1 : 1;
    }

    void minimax() {
        
    }

public:
    Game() {
        reset();
    }

    // Game Between Two Humans
    void play() {
        std::cout
<< "             _______________" << '\n'
<< "            |  ___________  |" << '\n'
<< "            | | TICTACTOE | |" << '\n'
<< "            | |___________| |" << '\n'
<< "            |_______________|" << "\n\n";


        show_input_pattern();

        // Game Loop
        while (1) {
            std::set<std::pair<int, int>> pos = available_positions();
            std::pair<int, int> action = choose_action (pos);
            switch_player(action);
            show_board();

            int win = check_winner();
            if (isEnd) {
                if (win == 1)
                    std::cout << "Player1 Wins!\n";
                else if (win == -1)
                    std::cout << "Player2 Wins!\n";
                else
                    std::cout << "The Game ends in a tie!\n";
                break;
            }
        }
    }

    // Play against computer
    void play_against_ai() {
        show_input_pattern();

        // Game Loop
        while (1) {
            // You'll go first, human should have the advantage coz let's face
            // it computer can do computation fast :(

            std::set<std::pair<int, int>> pos = available_positions();
            std::pair<int, int> action;

            if (player_turn == 1) {
                action = choose_action (pos);
            }
            else {
                minimax();
                action = choose_action (pos);
            }

            switch_player(action);
            show_board();

            int win = check_winner();
            if (isEnd) {
                if (win == 1)
                    std::cout << "Let's go Team Human ^_^!\n";
                else if (win == -1)
                    std::cout << "Computer Wins!\n";
                else
                    std::cout << "The Game ends in a tie! Not bad.\n";
                break;
            }
        }
    }
};


int main() {
    Game tictactoe;

    tictactoe.play();

    return 0;
}

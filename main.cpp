//! Author: Arindam

#include <iostream>
#include <cmath>
#include <array>
#include <set>
#include <limits>
#include <random>

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
        difficulty = 1;
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

        // For Diagonals
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
        std::cout << "Choose the position from below ...." << '\n';
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
    void switch_player (std::pair<int, int> pos) {
        board[pos.first][pos.second] = player_turn;
        player_turn = player_turn == 1 ? -1 : 1;
    }

    std::pair <int, int> minimax() {
        int best_score = INT_MAX;
        std::pair<int, int> action;
        int level = 0;

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = -1;

                    int score = max_search(level);

                    if (score < best_score) {
                        best_score = score;
                        action = std::make_pair(i, j);
                    }

                    board[i][j] = 0;
                }
            }
        }

        return action;
    }

    int max_search(int level) {
        int win = check_winner();
        if (isEnd) {
            isEnd = false;
            if (win == 1) return 10;
            else if (win == -1) return -10;
            else if (win == 0) return 0;
        }

        int score = INT_MIN;

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = 1;

                    score = std::max(score, min_search(level+1) - level);

                    board[i][j] = 0;
                }
            }
        }

        return score;
    }

    int min_search(int level) {
        int win = check_winner();
        if (isEnd) {
            isEnd = false;
            if (win == 1) return 10;
            else if (win == -1) return -10;
            else if (win == 0) return 0;
        }

        int score = INT_MAX;

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = -1;

                    score = std::min(score, max_search(level+1) + level);

                    board[i][j] = 0;
                }
            }
        }

        return score;
    }

    std::pair<int, int> random_moves(std::set<std::pair<int, int>> pos) {
        std::pair<int, int> action;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist9(0,8);

        while (1) {
            int idx = dist9(rng);
            action = std::make_pair(idx / BOARD_SIZE, idx % BOARD_SIZE);
            if (pos.find(action) != pos.end()) {
                break;
            }
        }

        return action;
    }


public:
    int difficulty;
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


        // Game Loop
        while (1) {
            show_input_pattern();
            std::set<std::pair<int, int>> pos = available_positions();
            std::pair<int, int> action = choose_action (pos);

            system("cls");
            switch_player(action);

            std::cout << "It's " << (player_turn == 1 ? "X" : "O")
                << "'s turn \n";

            show_board();

            int win = check_winner();
            if (isEnd) {
                if (win == 1)
                    std::cout << "X Wins!\n";
                else if (win == -1)
                    std::cout << "O Wins!\n";
                else
                    std::cout << "The Game ends in a tie!\n";
                break;
            }
        }
    }

    // Play against computer
    void play_against_ai() {
         std::cout
<< "             _______________" << '\n'
<< "            |  ___________  |" << '\n'
<< "            | | TICTACTOE | |" << '\n'
<< "            | |___________| |" << '\n'
<< "            |_______________|" << "\n\n";

        // Game Loop
        while (1) {
            show_input_pattern();
            // You'll go first, human should have the advantage coz let's face
            // it computer can do computation fast

            std::set<std::pair<int, int>> pos = available_positions();
            std::pair<int, int> action;

            if (player_turn == 1) {
                action = choose_action (pos);
            }
            else {
                action = difficulty == 2 ? minimax() : random_moves(pos);
            }

            system("cls");

            std::cout << "Position Choosed By Computer : "
                    << action.first * BOARD_SIZE + action.second << '\n';

            switch_player(action);
            show_board();

            int win = check_winner();
            if (isEnd) {
                if (win == 1) {
                    difficulty == 2 ?
                    std::cout << "If you are seeing this you will "
                        <<"probably fail the turing test XD!\n" :
                    std::cout << "Well done! You have won the game :)";
                }
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

    std::cout << "Welcome to game of TIC TAC TOE...\n" <<
        "Press 1 to Play Against your friend.\n" <<
        "Press 2 to Play Against Computer.\n";

    int input;
    std::cin >> input;

    system("cls");

    if (input == 1)
        tictactoe.play();
    else if (input == 2) {
        std::cout << "Choose your difficuilty level  \n"
            << "1 for Easy \n"
            << "2 for Hard \n";

        std::cin >> tictactoe.difficulty;
        system("cls");
        tictactoe.play_against_ai() ;
    }
    else
        std::cout << "Please choose from given options. \n";

    return 0;
}

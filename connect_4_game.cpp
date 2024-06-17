#include<bits/stdc++.h>
#include <chrono>
#include <windows.h>
using namespace std;

// by jvpcms


class connect_4 {

    private:
        int n, m, w;
        char** board;
        char piece_1 = 'X';
        char piece_2 = 'O';
        char space = '+';

        char divider_horiz = ' ';

        char player = piece_1;

        int made_moves = 0;

        bool strategic_opponent = false;
        int MIN_INF = -2, MAX_INF = 2;
        const int MAX_DEPTH = 10;
        vector<int> check_order;

    public:
        connect_4() {
            cout << "Enter the number of lines: "; cin >> this->n;
            cout << "Enter the number of columns: "; cin >> this->m;
            cout << "Enter the number of pieces in a row to win: "; cin >> this->w;

            this->board = new char*[n];
            for (int i = 0; i < n; i++) this->board[i] = new char[m];

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    this->board[i][j] = this->space;
                }
            }

            int p = this->m / 2;

            for (int i = 1; i <= this->m; i++) {
                check_order.push_back(p);
                p += (i % 2 == 0) ? i : -i;
            }
        }

        connect_4(int n, int m, int w=4) {
            this->n = n;
            this->m = m;
            this->w = w;
            
            this->board = new char*[n];
            for (int i = 0; i < n; i++) this->board[i] = new char[m];

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    this->board[i][j] = this->space;
                }
            }

            int p = this->m / 2;

            for (int i = 1; i <= this->m; i++) {
                check_order.push_back(p);
                p += (i % 2 == 0) ? i : -i;
            }
        }

        void display_board() {

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            for (int i = 0; i < this->n; i++) {
                for (int j = 0; j < this->m; j++) {

                    if (this->board[i][j] == this->piece_1) SetConsoleTextAttribute(hConsole, 12);
                    else if (this->board[i][j] == this->piece_2) SetConsoleTextAttribute(hConsole, 9);
                    
                    cout << this->board[i][j] << this->divider_horiz;

                    SetConsoleTextAttribute(hConsole, 15);
                }
                
                cout << '\n';
            }
        }

        void reset_board() {
            for (int i = 0; i < this->n; i++) {
                for (int j = 0; j < this->m; j++) {
                    this->board[i][j] = this->space;
                }
            }
            this->made_moves = 0;
        }

        void next_player() {
            this->player = (this->player == this->piece_1) ? this->piece_2 : this->piece_1;
        }

        bool is_valid_move(int col) {
            return this->board[0][col] == this->space and col >= 0 and col < this->m;
        }

        void place_piece(int col) {

            // col need to be validated first

            for (int line = this->n - 1; line >= 0; line--) {
                if (this->board[line][col] == this->space) {
                    this->board[line][col] = this->player;
                    this->made_moves++;
                    break;
                }
            }
        }

        void remove_piece(int col) {

            for (int line = 0; line < this->n; line++) {
                if (this->board[line][col] != this->space) {
                    this->board[line][col] = this->space;
                    this->made_moves--;
                    break;
                }
            }
        }

        bool check_win() {

            bool win = false;

            for (int line = 0; line < this->n; line++) {
                for (int col = 0; col < this->m; col++) {

                    char current = this->board[line][col];

                    if (current == this->space) continue;

                    // check right
                    for (int i = 1; i < this->w; i++) {
                        if (col + i >= this->m or this->board[line][col + i] != current) break;
                        if (i == this->w - 1) win = true;
                    }

                    // check down
                    for (int i = 1; i < this->w; i++) {
                        if (line + i >= this->n or this->board[line + i][col] != current) break;
                        if (i == this->w - 1) win = true;
                    }

                    // check diagonal (right down)
                    for (int i = 1; i < this->w; i++) {
                        if (line + i >= this->n or col + i >= this->m or this->board[line + i][col + i] != current) break;
                        if (i == this->w - 1) win = true;
                    }

                    // check diagonal (right up)
                    for (int i = 1; i < this->w; i++) {
                        if (line - i < 0 or col + i >= this->m or this->board[line - i][col + i] != current) break;
                        if (i == this->w - 1) win = true;
                    }
                }
            }

            return win;

        }

        bool board_is_full() {
            return this->made_moves >= this->n * this->m;
        }

        void player_move() {
            
            bool valid_move = false;

            while (!valid_move) {

                cout << '\n' << "Player " << this->player << " choose a column: ";
                int col; cin >> col; col--;

                if (is_valid_move(col)) {
                    valid_move = true;
                    place_piece(col);
                }

                if (!valid_move) {
                    cout << "Invalid move, try again." << '\n';
                }

                cout << '\n';
            }            
        }

        void bot_random_move() {
            int col = rand() % this->m;
            while (!is_valid_move(col)) col = rand() % this->m;

            place_piece(col);
        }

        int minimax(char **board, int depth, int alpha, int beta, bool isMaximizing) {

            if (check_win()) return (isMaximizing) ? -1 : 1;
            if (board_is_full() or depth == MAX_DEPTH) return 0;

            if (isMaximizing) {
                int bestScore = MIN_INF;

                for (int col : this->check_order) {
                    if (!is_valid_move(col)) continue;

                    place_piece(col);
                    next_player();

                    int score = minimax(this->board, depth + 1, alpha, beta, false);

                    remove_piece(col);
                    next_player();

                    bestScore = max(bestScore, score);

                    alpha = max(alpha, score);
                    if (beta <= alpha) break;
                }

                return bestScore;
            }

            else {
                int bestScore = MAX_INF;

                for (int col : this->check_order) {
                    if (!is_valid_move(col)) continue;

                    place_piece(col);
                    next_player();

                    int score = minimax(this->board, depth + 1, alpha, beta, true);

                    remove_piece(col);
                    next_player();

                    bestScore = min(bestScore, score);

                    beta = min(beta, score);
                    if (beta <= alpha) break;
                }

                return bestScore;
            }
            
        }

        void bot_strategic_move() {

            int bestScore = MIN_INF, bestCol = 0;

            for (int col : this->check_order) {

                if (!is_valid_move(col)) continue;

                place_piece(col);
                next_player();
                
                int score = minimax(this->board, 0, MIN_INF, MAX_INF, false);

                remove_piece(col);
                next_player();
                
                if (score > bestScore) {
                    bestScore = score;
                    bestCol = col;
                }
            }

            place_piece(bestCol);
  
        }

        void play() {
            
            cout << "Who do you want to play against? (s - Strategic / r - Random): ";
            char choice; cin >> choice; cout << '\n';

            if (choice == 's') this->strategic_opponent = true;

            reset_board();

            while (!board_is_full()) {

                (this->strategic_opponent) ? bot_strategic_move() : bot_random_move();

                display_board();

                if (check_win()) {
                    cout << '\n' << "Player " << this->player << " wins!";
                    return;
                }
                next_player();

                if (board_is_full()) break;

                player_move();

                if (check_win()) {
                    display_board();
                    cout << '\n' << "Player " << this->player << " wins!";
                    return;
                }
                next_player();
            }

            cout << '\n' << "It's a draw!";
            return;
        }

        int play_bot_vs_bot(int tests=1) {

            // Expected:
            // strategic vs random: mostly wins, some draws
            // random vs random: wins and defeats close to 50%, some draws
            // strategic vs strategic: mostly draws
            // random vs strategic: mostly defeats, some draws, almost no victories

            int victory = 0, defeat = 0, draw = 0;

            auto start = chrono::high_resolution_clock::now();

            for (int i = 0; i < tests; i++) {
                
                reset_board();

                while (!board_is_full()) {

                    bot_strategic_move();

                    if (check_win()) {victory++; break;}
                    next_player();

                    if (board_is_full()) break;

                    bot_random_move();

                    if (check_win()) {defeat++; break;}
                    next_player();
                }

                if (board_is_full()) draw++;
            }        
        
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

            cout << '\n' << "Victories: " << victory;
            cout << '\n' << "Defeats: " << defeat;
            cout << '\n' << "Draws: " << draw;

            cout << '\n' << "Time: " << duration.count() << " ms";

            return 0;
        }
    

};

int main() {
    
    srand(time(NULL));

    connect_4 game(6, 7);
    game.play();

    return 0;
}
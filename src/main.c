#include "checkers.h"
#include <stdio.h>

int main() {
    char board[WIDTH][HEIGHT];
    int score;

    checkers_setup_board(board);
    checkers_print_board(board);
    score = checkers_evaluate_board(board);

    printf("%d\n", score);

    return 0;
}

#include "checkers.h"
#include <stdio.h>
#include <stdlib.h>

void checkers_setup_board(char board[WIDTH][HEIGHT]) {
    int x, y;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if ((x + y) % 2) {
                if (y < SETUP_ROWS) {
                    board[x][y] = IS_PIECE | IS_WHITE;
                } else if (HEIGHT - y <= SETUP_ROWS) {
                    board[x][y] = IS_PIECE;
                } else {
                    board[x][y] = EMPTY;
                }
            } else {
                board[x][y] = EMPTY;
            }
        }
    }
}

void checkers_print_board(char board[WIDTH][HEIGHT]) {
    int x, y;
    char piece;
    for (y = 0; y < HEIGHT; y++) {
        if (HEIGHT - y < 10) {
            printf(" ");
        }
        printf("%d ", HEIGHT - y);
        for (x = 0; x < WIDTH; x++) {
            piece = board[x][y];
            if ((x + y) % 2 == 0) {
                printf("\033[47m ");
            } else {
                printf("\033[0m ");
            }
            checkers_print_piece(piece);
        }
        printf("\033[0m\n");
    }
    printf("   ");
    for (x = 0; x < WIDTH; x++) {
        printf(" %c ", 'A' + x);
    }
    printf("\n");
}

void checkers_print_piece(char piece) {
    if (piece & IS_PIECE) {
        if (piece & IS_WHITE) {
            if (piece & IS_KING) {
                printf("\u26C1 ");
            } else {
                printf("\u26C0 ");
            }
        } else {
            if (piece & IS_KING) {
                printf("\u26C3 ");
            } else {
                printf("\u26C2 ");
            }
        }
    } else {
        printf("  ");
    }
}

int checkers_evaluate_board(char board[WIDTH][HEIGHT]) {
    int x, y;
    char piece;
    int scores[] = {0, 0};
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            piece = board[x][y];
            if (piece & IS_PIECE) {
                scores[(piece >> 1) & 1] += checkers_evaluate_piece(board, x, y);
            }
        }
    }
    return scores[0] - scores[1];
}

int checkers_evaluate_piece(char board[WIDTH][HEIGHT], int x, int y) {
    return board[x][y] & IS_WHITE;
}


#include "checkers.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void checkers_play_game() {
    CheckersGame game;
    char buffer[32];
    int x, y;

    checkers_setup_game(&game, 10, 10, 4);
    checkers_print_board(&game);
    fgets(buffer, 32, stdin);

    if (checkers_parse_input(&game, buffer, &x, &y)) {
        printf("Invalid input: %s", buffer);
    }
    printf("x: %d y: %d\n", x, y);

    free(game.board);
}

int checkers_parse_input(CheckersGame *game, char buffer[], int *x, int *y) {
    if (isupper(buffer[0])) {
        *x = buffer[0] - 'A';
    } else {
        return 1;
    }
    if (isdigit(buffer[1])) {
        *y = buffer[1] - '0';
    } else {
        return 1;
    }
    if (isdigit(buffer[2])) {
        *y = 10 * *y + buffer[2] - '0';
    }
    *y = game->height - *y;
    return *x >= game->width || *y >= game->height || *y < 0;
}

void checkers_setup_game(CheckersGame *game, int width, int height, int filled_rows) {
    int x, y, i;
    game->board = malloc(width * height);
    game->width = width;
    game->height = height;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            i = y * game->width + x;
            if ((x + y) % 2) {
                if (y < filled_rows) {
                    PIECE_AT_IDX(game, i) = IS_PIECE | IS_WHITE;
                } else if (height - y <= filled_rows) {
                    PIECE_AT_IDX(game, i) = IS_PIECE;
                } else {
                    PIECE_AT_IDX(game, i) = EMPTY;
                }
            } else {
                PIECE_AT_IDX(game, i) = EMPTY;
            }
        }
    }
}

void checkers_print_board(CheckersGame *game) {
    int x, y;
    printf("\033[2J");
    for (y = 0; y < game->height; y++) {
        if (game->height - y < 10) {
            printf(" ");
        }
        printf("%d ", game->height - y);
        for (x = 0; x < game->width; x++) {
            if ((x + y) % 2 == 0) {
                printf("\033[47m ");
            } else {
                printf("\033[0m ");
            }
            checkers_print_piece(PIECE_AT(game, x, y));
        }
        printf("\033[0m\n");
    }
    printf("   ");
    for (x = 0; x < game->width; x++) {
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

int checkers_evaluate_board(CheckersGame *game) {
    int x, y;
    char piece;
    int scores[] = {0, 0};
    for (y = 0; y < game->height; y++) {
        for (x = 0; x < game->width; x++) {
            piece = PIECE_AT(game, x, y);
            if (piece & IS_PIECE) {
                scores[(piece >> 1) & 1] += checkers_evaluate_piece(game, x, y);
            }
        }
    }
    return scores[0] - scores[1];
}

int checkers_evaluate_piece(CheckersGame *game, int x, int y) {
    if (PIECE_AT(game, x, y) & IS_PIECE) {
        return 1;
    }
    return 0;
}

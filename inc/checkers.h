#ifndef CHECKERS_H
#define CHECKERS_H

// Piece structure (0 = LSB):
// 0: 0 if piece is empty - overrides others
// 1: 0 if piece is black, else white
// 2: 0 if piece is man, else king
// 3: 0 if piece is black square, else white square
#define EMPTY    0x0
#define IS_PIECE 0x1
#define IS_WHITE 0x2
#define IS_KING  0x4

#define SETUP_ROWS 4
#define WIDTH      10
#define HEIGHT     10

#define PIECE_AT(game, x, y) game->board[y * game->width + x]
#define PIECE_AT_IDX(game, i) game->board[i]

typedef struct {
    char *board;
    int width;
    int height;
} CheckersGame;

void checkers_play_game();
int checkers_parse_input(CheckersGame *game, char buffer[], int *x, int *y);
void checkers_setup_game(CheckersGame *game, int width, int height, int filled_rows);
void checkers_print_board(CheckersGame *game);
void checkers_print_piece(char piece);
int checkers_evaluate_board(CheckersGame *game);
int checkers_evaluate_piece(CheckersGame *game, int x, int y);

#endif

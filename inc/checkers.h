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

typedef struct {
    char *board;
    int width;
    int height;
} CheckersGame;

void checkers_setup_board(char board[WIDTH][HEIGHT]);
void checkers_print_board(char board[WIDTH][HEIGHT]);
void checkers_print_piece(char piece);
int checkers_evaluate_board(char board[WIDTH][HEIGHT]);
int checkers_evaluate_piece(char board[WIDTH][HEIGHT], int x, int y);

#endif

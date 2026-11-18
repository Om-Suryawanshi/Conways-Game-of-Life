#ifndef BOARD_H
#define BOARD_H

typedef struct {
    int *current;
    int *next;
    int width;
    int height;
} Board;

Board* init_board(void);
void free_board(Board *board);
void clear_board(Board* board);

int get_value_from_board(Board* board, int x, int y);
int set_value_in_board(Board* board, int x, int y, int value);

void swap_boards(Board* board);

#endif
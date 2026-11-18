#ifndef GAME_H
#define GAME_H
#include "board.h"

const int count_neighbours(Board* board, int x, int y);
void update_board(Board* board);
void randomize_board(Board* board, double prob);
void sleep_ms(unsigned int millisecs);

#endif
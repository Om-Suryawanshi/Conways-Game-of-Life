#include "game.h"
#include <stdlib.h>

const int count_neighbours(Board* board, int x, int y)
{
    if (!board || x < 0 || y < 0 || x >= board->width || y >= board->height)
        return -1;

    int neighbours = 0;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue;
            
            int value = get_value_from_board(board, x + dx, y + dy);

            if (value == 1)
                neighbours++;
        }
    }
    return neighbours;
}

void update_board(Board* board)
{
    if (!board)
        return;

    for (int y = 0; y < board->height; y++)
    {
        for(int x = 0; x < board->width; x++)
        {
            int alive = get_value_from_board(board, x, y);
            int neighbours = count_neighbours(board, x, y);

            int next_state = 0;

            if (alive == 1)
            {
                if (neighbours == 2 || neighbours == 3)
                    next_state = 1;
            }
            else
            {
                if (neighbours == 3)
                    next_state = 1;
            }

            set_value_in_board(board, x, y, next_state);
        }
    }
    swap_boards(board);
}

void randomize_board(Board* board, double prob)
{
    if (!board || prob < 0.0 || prob > 1.0)
        return;

    size_t size = (size_t)board->width * board->height;

    for (size_t i = 0; i < size; i++)
    {
        int alive = ((double)rand() / ((double)RAND_MAX + 1.0) < prob);

        board->current[i] = alive;
        board->next[i] = alive;
    }
}

#ifdef _WIN32

#include <windows.h>

void sleep_ms(unsigned int millisecs)
{
    Sleep(millisecs);
}

#elif defined(__linux__)

#include <time.h>

void sleep_ms(unsigned int millisecs)
{
    struct timespec ts;

    ts.tv_sec = millisecs / 1000;
    ts.tv_nsec = (long)(millisecs % 1000) * 1000000L;

    nanosleep(&ts, NULL);
}

#else
#error "Unsupported OS"
#endif
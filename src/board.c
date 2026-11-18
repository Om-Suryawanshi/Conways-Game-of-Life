#include "board.h"
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#ifdef _WIN32
#include <windows.h>

static int set_console_dimensions(int *width, int *height)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
        return -1;

    *width = info.srWindow.Right - info.srWindow.Left + 1;
    *height = info.srWindow.Bottom - info.srWindow.Top + 1;

    return 0;
}

#elif defined(__linux__)

#include <sys/ioctl.h>
#include <unistd.h>

static int set_console_dimensions(int *width, int* height)
{
    struct winsize ws;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return -1;

    *width = ws.ws_col;
    *height = ws.ws_row;

    return 0;
}

#else
#error "Unsupported OS"
#endif

Board* init_board()
{
    Board* board = malloc(sizeof(Board));
    if (!board)
        return NULL;
    
    if(set_console_dimensions(&board->width, &board->height) != 0 || board->width <= 0 || board->height <= 0)
    {
        free(board);
        return NULL;
    }

    size_t width = (size_t)board->width;
    size_t height = (size_t)board->height;

    if (width > SIZE_MAX / height)
    {
        free(board);
        return NULL;
    }

    size_t size = width * height;

    board->current = calloc(size, sizeof(int));
    board->next = calloc(size, sizeof(int));

    if (!board->current || !board->next)
    {
        free_board(board);
        return NULL;
    }

    return board;
}

void free_board(Board *board)
{
    if (!board)
        return;

    free(board->current);
    free(board->next);
    free(board);
}

void clear_board(Board* board)
{
    if (!board)
        return;

    size_t size = (size_t)board->width * (size_t)board->height;

    for (size_t i = 0; i < size; i++)
    {
        board->current[i] = 0;
        board->next[i] = 0;
    }
}

int get_value_from_board(Board* board, int x, int y)
{
    if (!board || x < 0 || y < 0 || x >= board->width || y >= board->height)
        return -1;
    
    size_t index = (size_t)y * board->width + x;
    return board->current[index];
}

int set_value_in_board(Board* board, int x, int y, int value)
{
    if (!board || x < 0 || y < 0 || x >= board->width || y >= board->height)
        return -1;

    size_t index = (size_t)y * board->width + x;
    board->next[index] = value;
    return 0;
}

void swap_boards(Board* board)
{
    if (!board)
        return;

    int* temp = board->current;
    
    board->current = board->next;
    board->next = temp;
}
#include "display.h"
#include <stdio.h>

void clear_display()
{
    // \033[H Moves the cursor to topleft.
    // \033[J clears the screen from cursor down to the end of the screen buffer.
    printf("\033[H\033[J");
    fflush(stdout);
}

void reset_cursor(void)
{
    printf("\033[H");
}

void render_display(int *matrix, int width, int height)
{
    if (!matrix || width <= 0 || height <= 0)
        return;

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int index = y * width + x;

            if (matrix[index] == 1)
                printf("#");  // Alive
            else
                printf(".");
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);
}
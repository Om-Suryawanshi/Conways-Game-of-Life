#include "display.h"
#include <stdio.h>

void clear_display()
{
    // \033[H Moves the cursor to topleft.
    // \033[J clears the screen from cursor down to the end of the screen buffer.
    printf("\033[H\033[J");
}

void render_display(int matrix[WIDTH][HEIGHT])
{
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            // printf("%d", matrix[i][j]);
            if (matrix[i][j] == 1)
                printf("#");  // Alive
            else
                printf(".");
        }
        printf("\n");
    }
    printf("\n");
}
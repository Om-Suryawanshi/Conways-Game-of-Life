#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "game.h"
#include "display.h"

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));

	Board* board = init_board();

	if (!board)
	{
		fprintf(stderr, "Failed to initialize board\n");	
		return -1;
	}

	randomize_board(board, 0.3);

	clear_display();
	while(1)
	{
		// clear_display();
		reset_cursor();
		render_display(board->current, board->width, board->height);
		update_board(board);
		sleep_ms(150);
	}

	free_board(board);

	return 0;
}

#include "ai.h"

// Returns coordinates of a random free spot on the field
void ai_rand_cell(int **matr, COORDS *coord)
{
	int rand_cell;
	int count_free_cell = ai_cells_left;
	rand_cell = (int)(((double) rand() * count_free_cell / (double) RAND_MAX));

//DEBUG_PRINT(printf("rand(0-%d): %d\n",count_free_cell,rand_cell))

	for (int i = 0, count_cell = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (matr[i][j] == CELL_NONE) {
				if (count_cell++ == rand_cell) {
					coord->x = j;
					coord->y = i;

//DEBUG_PRINT(printf("return_coord.x: %d\n", return_coord.x);printf("return_coord.y: %d\n", return_coord.y);)

					return;
				}
			}
		}
	}
	return;
}


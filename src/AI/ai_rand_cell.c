#include "ai.h"
// Returns coordinates of a random free spot on the field
int ai_rand_cell(int **matr, COORDS *coord, DIRECTION_WAY const change)
{
	int rand_cell;
	int count_free_cell = 0;
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			if(matr[i][j] == CELL_NONE)
				count_free_cell++;

	rand_cell = (int)(((double) rand() * count_free_cell / (double) RAND_MAX));
	if (change == Y_X) {
		for (int y = 0, count_cell = 0; y < SIZE; ++y) {
			for (int x = 0; x < SIZE; ++x) {
				if (matr[y][x] == CELL_NONE) {
					if (count_cell++ == rand_cell) {
						coord->x = x;
						coord->y = y;
						return 1;
					}
				}
			}
		}
	} else if (change == X_Y) {
		for (int y  = 0, count_cell = 0; y < SIZE; ++y) {
			for (int x = 0; x < SIZE; ++x) {
				if (matr[x][y] == CELL_NONE) {
					if (count_cell++ == rand_cell) {
						coord->x = x;
						coord->y = y;
						return 1;
					}
				}
			}
		}
	}
	return - 1;
}


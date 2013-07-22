#include "ai.h"
// Returns coordinates of a random free spot on the field
int ai_rand_cell(int **matr, COORDS *coord, DIRECTION_WAY const change)
{
	int rand_cell;
	int count_free_cell = ai_cells_left;
	rand_cell = (int)(((double) rand() * count_free_cell / (double) RAND_MAX));
//	printf("rand_cell: %d\n", rand_cell);
//DEBUG_PRINT(printf("rand(0-%d): %d\n",count_free_cell,rand_cell))
	if (change == Y_X) {
		for (int y = 0, count_cell = 0; y < SIZE; ++y) {
			for (int x = 0; x < SIZE; ++x) {
				if (matr[y][x] == CELL_NONE) {
					if (count_cell++ == rand_cell) {
						printf("matr1; %d\n", matr[y][x]);
						coord->x = x;
						coord->y = y;
	printf("count_free_cell: %d\n", count_free_cell);
	printf("rand_cell: %d\n", rand_cell);
//DEBUG_PRINT(printf("return_coord.x: %d\n", return_coord.x);printf("return_coord.y: %d\n", return_coord.y);)
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
						printf("matr2; %d\n", matr[x][y]);
						coord->x = x;
	printf("count_free_cell: %d\n", count_free_cell);
	printf("rand_cell: %d\n", rand_cell);
						coord->y = y;
//DEBUG_PRINT(printf("return_coord.x: %d\n", return_coord.x);printf("return_coord.y: %d\n", return_coord.y);)
						return 1;
					}
				}
			}
		}
	}
	printf("count_free_cell: %d\n", count_free_cell);
	printf("rand_cell: %d\n", rand_cell);
//	printf("exit 1\n");
	return - 1;
}


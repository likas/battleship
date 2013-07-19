#include "ai.h"

void ai_rand_cell_wrap(int **matr, COORDS *coord, int const count_free_cell)
{
	int ai_cells_left_temp = ai_cells_left;
	ai_cells_left = count_free_cell;
	ai_rand_cell(matr, coord);
	ai_cells_left = ai_cells_left_temp;
}

/* функция во возвращает количество пробных клеток корабля установленных на матрице*/
int conditional_ship(int **matr, COORDS *coord, int const size_ship, AI_DIRECTION *direct, int *way)
{
//	printf("__%s__\n", __func__);
	int check_size_ship = 0; // количество клеток корабял установленное на матрице
	int r_loc = rand() % 4; // 0 - вверх/ 1 - вправо/ 2 - вниз/ 3 - влево
	int count = 4; // флаг для цикла по r_loc если текущий r_loc не пригоден
	while (count) {
		check_size_ship = 0;
//		printf("count: %d\n", count);
//		printf("check_size_ship: %d\n", check_size_ship);
//		printf("way: %d\n", *way);
//		getchar();
//		printf("r_loc: %d\n", r_loc);
		switch (r_loc) {
			case 0:
				direct->dx = 0;
				direct->dy = -1;
				break;
			case 1:
				direct->dx = 1;
				direct->dy = 0;
				break;
			case 2:
				direct->dx = 0;
				direct->dy = 1;
				break;
			case 3:
				direct->dx = -1;
				direct->dy = 0;
				break;
		}
		for (int x = coord->x, y = coord->y; ; x += direct->dx, y += direct->dy) {
//			printf("__%d__%d__\n", y, x);
			if ((x >= 0) && (x < SIZE) && (y >= 0) && (y < SIZE)) {
				if (matr[y][x] == CELL_NONE) {
					if (++check_size_ship == size_ship) {
						*way = r_loc;
						return size_ship;
					}
				} else {
					count = 1;
					break;
				}
			} else {
				count = 1;
				break;
			}
		}
		if (++r_loc >= 4)
			r_loc = 0;
		--count;
	}
	return check_size_ship;
}


void set_ship(int **matr, COORDS *coord, AI_DIRECTION *direct, int *count_free_cell, int const size_ship, int way)
{
	int count_cell_ship = 0;
	int count_motion_forward,
		count_motion_down,
		count_motion_back,
		count_motion_up; // движение вокруг корабля вперед, вниз, назад, вверх для проставления клеток, в которые нельзя ставить корабли
	int x, y;
//	printf("coord->x: %d\ncoord->y: %d\nway: %d\n", coord->x, coord->y, way);
//	printf("direct.dx: %d\ndirect.dy: %d\n", direct->dx, direct->dy);
	for (x = coord->x, y = coord->y; ; x += direct->dx, y += direct->dy) {
			matr[y][x] = CELL_SHIP;
			--(*count_free_cell);
			if (++count_cell_ship == size_ship)
				break;
	}
//	printf("x: %d\ny: %d\n", x, y);
	switch (way) { // 0 - вверх/ 1 - вправо/ 2 - вниз/ 3 - влево
		case 0:
			x = coord->x - 1;
			y = coord->y - size_ship;
			count_motion_forward = 2;
			count_motion_down = size_ship + 1;
			count_motion_back = 2;
			count_motion_up = size_ship;
			break;
		case 1:
			x = coord->x - 1;
			y = coord->y - 1;
			count_motion_forward = size_ship + 1;
			count_motion_down = 2;
			count_motion_back = size_ship + 1;
			count_motion_up = 1;
			break;
		case 2:
			x = coord->x - 1;
			y = coord->y - 1;
			count_motion_forward = 2;
			count_motion_down = size_ship + 1;
			count_motion_back = 2;
			count_motion_up = size_ship;
			break;
		case 3:
			x = coord->x - size_ship;
			y = coord->y - 1;
			count_motion_forward = size_ship + 1;
			count_motion_down = 2;
			count_motion_back = size_ship + 1;
			count_motion_up = 1;
			break;
	}
	while (1) {
//		printf("x: %d\ny: %d\n", x, y);
		if ((x >= 0) && (x < SIZE) && (y >= 0) && (y < SIZE)) {
			if (matr[y][x] != CELL_MISS) {
				matr[y][x] = CELL_MISS;
				--(*count_free_cell);
			}
		}
		if (count_motion_forward) {
//			printf("forward\n");
			x += 1;
			--count_motion_forward;
		} else if (count_motion_down) {
//			printf("down\n");
			y += 1;
			--count_motion_down;
		} else if (count_motion_back) {
			x -= 1;
//			printf("back\n");
			--count_motion_back;
		} else if (count_motion_up) {
			y -= 1;
//			printf("up\n");
			--count_motion_up;
		} else {
			break;
		}
//		print_matr(matr);
//		getchar();
	}
}

void rand_loc_ship(int **matr, int const size_ship, int *count_free_cell)
{
	COORDS coord;
	AI_DIRECTION direct; // напрвление корабля в векторе (1,0) - вправо/(-1,0) - влево/(0,1) - вверх/(0,-1) - вниз
	
	int way; // направление корабля 0/1/2/3

	do {
		ai_rand_cell_wrap(matr, &coord, *count_free_cell);
//		printf("rand_loc_ship\nx:%d\ny:%d\nsize_ship:%d\ncount_free_cell:%d\n", coord.x, coord.y, size_ship, *count_free_cell);
	} while(conditional_ship(matr, &coord, size_ship, &direct, &way) != size_ship);
	set_ship(matr, &coord, &direct, count_free_cell, size_ship, way);
}


int ai_rand_matr(int **matr)
{
	srand(time(NULL));
	int count_free_cell = SIZE * SIZE;
//nt **matr = (int**)malloc(SIZE * sizeof(int*));
	if (matr == NULL) {
//		printf("error no memory for <**matr> in <%s>\n", __func__);
//		perror("");
//		(1);
		return -1;
	}
	for (int i = 0; i < SIZE; ++i) {
//matr[i] = (int*)calloc(SIZE, sizeof(int));
		if (matr[i] == NULL) {
//			printf("error no memory for <matr[%d]> in <%s>\n", i, __func__);
//			perror("");
//			exit(1);
			return -2;
		}
	}

	rand_loc_ship(matr, 4, &count_free_cell);
//	printf("count_free_cells: %d\n", count_free_cell);
//	print_matr(matr);
	rand_loc_ship(matr, 3, &count_free_cell);
//	printf("count_free_cells: %d\n", count_free_cell);
//	print_matr(matr);
	rand_loc_ship(matr, 3, &count_free_cell);
//	printf("count_free_cells: %d\n", count_free_cell);
//	print_matr(matr);
	rand_loc_ship(matr, 2, &count_free_cell);
//	printf("count_free_cells: %d\n", count_free_cell);
//	print_matr(matr);
	rand_loc_ship(matr, 2, &count_free_cell);
//	printf("count_free_cells: %d\n", count_free_cell);
//	print_matr(matr);
	rand_loc_ship(matr, 2, &count_free_cell);
//	printf("count_free_cells: %d\n", count_free_cell);
//	print_matr(matr);
	rand_loc_ship(matr, 1, &count_free_cell);
//	printf("count_free_cells: %d\n", count_free_cell);
//	print_matr(matr);
	rand_loc_ship(matr, 1, &count_free_cell);
//	printf("count_free_cells: %d\n", count_free_cell);
//	print_matr(matr);
	rand_loc_ship(matr, 1, &count_free_cell);
//	printf("count_free_cells: %d\n", count_free_cell);
//	print_matr(matr);
	rand_loc_ship(matr, 1, &count_free_cell);
//	printf("count_free_cells: %d\n", count_free_cell);
//	print_matr(matr);
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (matr[i][j] != CELL_SHIP)
				matr[i][j] = CELL_NONE;
		}
	}

	return 0;
}

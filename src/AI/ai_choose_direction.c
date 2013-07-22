#include "ai.h"

void ai_choose_direction(enum _REQUESTS state)
{
	COORDS coords = (ai_last_shot_suc.x == -1 && ai_last_shot_suc.y == -1) ? ai_last_shot : ai_last_shot_suc;
	if(got_target != 2)
	{
		int N_sides = 0;
		int avalible_sides[4] = { 0 };
		if( coords.x > 0 && ai_enemy_field[coords.x - 1][coords.y] == CELL_NONE )
			N_sides++, avalible_sides[0] = 1;
		if( coords.y > 0 && ai_enemy_field[coords.x][coords.y - 1] == CELL_NONE )
			N_sides++, avalible_sides[1] = 1;
		if( coords.x < SIZE - 1 && ai_enemy_field[coords.x + 1][coords.y] == CELL_NONE )
			N_sides++, avalible_sides[2] = 1;
		if( coords.y < SIZE - 1 && ai_enemy_field[coords.x][coords.y + 1] == CELL_NONE )	
			N_sides++, avalible_sides[3] = 1;
		int direction = (((double)rand() / RAND_MAX) * N_sides);
		while(avalible_sides[direction % 4] != 1)
			direction++;
		switch(direction)
 		{
			case 0: ai_direction.dx = -1, ai_direction.dy = 0; break;
			case 1: ai_direction.dx = 0, ai_direction.dy = -1; break;
			case 2: ai_direction.dx = 1, ai_direction.dy = 0; break;
			case 3: ai_direction.dx = 0, ai_direction.dy = 1; break;
		}
		printf("Dir: %d %d N: %d\n", ai_direction.dx, ai_direction.dy, N_sides);
	}
	else if(state == REQ_MISS)
	{
		ai_direction.dx *= -1;
		ai_direction.dy *= -1;
		while(ai_enemy_field[ai_last_shot.x + ai_direction.dx][ai_last_shot.y + ai_direction.dy] != CELL_NONE)
			ai_last_shot.x += ai_direction.dx, ai_last_shot.y += ai_direction.dy;
	}
}

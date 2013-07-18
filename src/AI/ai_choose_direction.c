#include "ai.h"

void ai_choose_direction(enum _CELL_STATE state)
{
	if( ai_last_shot_suc.x == -1 && ai_last_shot_suc.y == -1)
	{
		int N_sides = 0;
		int avalible_sides[4];
		if(ai_last_shot.x > 0 && ai_enemy_field[ai_last_shot.x - 1][ai_last_shot.y] == CELL_NONE)
			N_sides++, avalible_sides[0] = 1;
		else
			avalible_sides[0] = 0;
		if( ai_last_shot.y > 0 && ai_enemy_field[ai_last_shot.x][ai_last_shot.y - 1] == CELL_NONE )
			N_sides++, avalible_sides[1] = 1;
		else
			avalible_sides[1] = 0;
		if( ai_last_shot.x < SIZE - 1 && ai_enemy_field[ai_last_shot.x + 1][ai_last_shot.y] == CELL_NONE )
			N_sides++, avalible_sides[2] = 1;
		else
			avalible_sides[2] = 0;
		if( ai_last_shot.y < SIZE - 1 && ai_enemy_field[ai_last_shot.x][ai_last_shot.y + 1] == CELL_NONE )	
			N_sides++, avalible_sides[3] = 1;
		else
			avalible_sides[3] = 0;
		int direction = (rand() / RAND_MAX) * N_sides;
		while(avalible_sides[direction % 4] != 1)
			direction++;
		switch(direction)
 		{
			case 0: ai_direction.dx = -1, ai_direction.dy = 0; break;
			case 1: ai_direction.dx = 0, ai_direction.dy = -1; break;
			case 2: ai_direction.dx = 1, ai_direction.dy = 0; break;
			case 3: ai_direction.dx = 0, ai_direction.dy = 1; break;
		}
	}
	else if(state == CELL_MISS)
	{
		ai_direction.dx *= -1;
		ai_direction.dy *= -1;
		while(ai_enemy_field[ai_last_shot.x + ai_direction.dx][ai_last_shot.y + ai_direction.dy] != CELL_NONE)
			ai_last_shot.x += ai_direction.dx, ai_last_shot.y += ai_direction.dy;
	}
}

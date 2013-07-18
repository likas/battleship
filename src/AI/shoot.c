#include "ai.h"
COORDS ai_last_shot = {-1, -1};
COORDS ai_last_shot_suc = {-1, -1};
AI_DIRECTION ai_direction = {0, 0};
int got_target = 0;

int ai_set_field(int **field)
{
	if(!field)
		return 0;
	player_field = field;
	return 1;
}

int ai_shoot(COORDS *coords)
{
	if(!coords)
		return 0;
	
	if( !got_target )
	{
		ai_rand_cell(ai_enemy_field, coords);	
		ai_last_shot = *coords;
		return 1;
	}
	
	coords->x = ai_last_shot.x + ai_direction.dx;
	coords->y = ai_last_shot.y + ai_direction.dy;	
	ai_last_shot = *coords;
	return 1;
}

int ai_hit(COORDS coords)
{
	if(ai_player_field[coords.x][coords.y] == CELL_SHIP)	
		ai_player_field[coords.x][coords.y] = CELL_SHIP_FIRE;
}

void ai_get_respond(enum _CELL_STATE state)
{
	ai_enemy_field[ai_last_shot.x][ai_last_shot.y] = state;
	
	if( !got_target && state == CELL_SHIP_FIRE)
		got_target = 1;
	if( got_target && state != CELL_SHIP_DEAD)
	{
		got_target = 0;
		ai_ship_mark_dead();
		ai_last_shot_suc.x = -1;
		ai_last_shot_suc.y = -1;
	}

	if( got_target )
		ai_choose_direction(state);
	
	if(state == CELL_SHIP_FIRE)
		ai_last_shot_suc = ai_last_shot;
}

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

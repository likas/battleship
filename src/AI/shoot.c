#include "ai.h"
AI_COORDS ai_last_shot = {0, 0};
AI_COORDS ai_last_shot_suc = {0, 0};
AI_DIRECTION ai_direction = {0, 0}

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
	
	if(	!ai_direction.dx && !ai_direction.dy )
	{
		ai_random_shot(ai_enemry_field, coords);	
		ai_last_shot = *coords;
		return 1;
	}
	
	
}

int ai_hit(COORDS coords)
{
	
}

void ai_get_respond(CELL_STATE state)
{
	ai_enemy_field[ai_last_shot.x][ai_last_shot.y] = state;
}

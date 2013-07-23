#include "ai.h"

// makes AI shoot in chosen direction if he has a target to shoot 
// otherwise he makes a random shot in a free spot on the field
int ai_shoot( COORDS *coords )
{
	if( coords == NULL ) 
		return 0;
	
	if( !got_target )
	{
		ai_rand_cell(ai_enemy_field, coords, X_Y);	
		if(coords->x == -1 && coords->y == -1)
			return 0;
		ai_last_shot.x = coords->x;
		ai_last_shot.y = coords->y;
		return 1;
	}
	
    if(ai_last_shot_suc.x + ai_direction.dx > -1 && 
	   ai_last_shot_suc.y + ai_direction.dy > -1 && 
	   ai_last_shot_suc.x + ai_direction.dx < SIZE && 
	   ai_last_shot_suc.y + ai_direction.dy < SIZE &&
	   ai_enemy_field[ai_last_shot_suc.x + ai_direction.dx]
				     [ai_last_shot_suc.y + ai_direction.dy] == CELL_NONE)
	{ 
		coords->x = ai_last_shot_suc.x + ai_direction.dx;
		coords->y = ai_last_shot_suc.y + ai_direction.dy;
	}
	else
	{
		ai_direction.dx *= -1;
		ai_direction.dy *= -1;
		coords->x = ai_last_shot_suc.x;
		coords->y = ai_last_shot_suc.y;
		do
		{
			coords->x = coords->x + ai_direction.dx;
			coords->y = coords->y + ai_direction.dy;
		}
		while(ai_enemy_field[coords->x][coords->y] != CELL_NONE);
    	
		if(coords->x == -1 && coords->y == -1)
			return 0;
		
		ai_last_shot_suc.x = coords->x - ai_direction.dx;
		ai_last_shot_suc.y = coords->y - ai_direction.dy;
	}
	ai_last_shot.x = coords->x;
	ai_last_shot.y = coords->y;
	return 1;
}

#include "ai.h"

// makes AI shoot in chosen direction if he has a target to shoot 
// otherwise he makes a random shot in a free spot on the field
int ai_shoot( COORDS *coords )
{
	if( coords == NULL ) {
		return 0;
	}
	
	if( !got_target )
	{
		ai_rand_cell(ai_enemy_field, coords, X_Y);	
		ai_cells_left--;
		ai_last_shot.x = coords->x;
		ai_last_shot.y = coords->y;
		return 1;
	}
	
	coords->x = ai_last_shot_suc.x + ai_direction.dx;
	coords->y = ai_last_shot_suc.y + ai_direction.dy;	
	ai_last_shot.x = coords->x;
	ai_last_shot.y = coords->y;
	ai_cells_left--;
	return 1;
}

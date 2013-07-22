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
		printf("RANDOOOM!\n");
		ai_rand_cell(ai_enemy_field, coords);	
		printf("Random shot %d %d\n", coords->x, coords->y);
		ai_cells_left--;
		ai_last_shot = *coords;
		return 1;
	}
	
	coords->x = ai_last_shot.x + ai_direction.dx;
	coords->y = ai_last_shot.y + ai_direction.dy;	
	printf("Strateg shot %d %d\n", coords->x, coords->y);
	
	ai_last_shot = *coords;
	return 1;
}

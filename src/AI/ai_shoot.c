#include "ai.h"

int ai_shoot(COORDS *coords)
{
	if(!coords)
		return 0;
	
	if( !got_target )
	{
		printf("RANDOOOM!\n");
		ai_rand_cell(ai_enemy_field, coords);	
		printf("Random shot %d %d\n", coords->x, coords->y);
		ai_cells_left--;
		ai_last_shot.x = coords->x;
		ai_last_shot.y = coords->y;
		return 1;
	}
	
	coords->x = ai_last_shot_suc.x + ai_direction.dx;
	coords->y = ai_last_shot_suc.y + ai_direction.dy;	
	printf("Strateg shot %d %d\n", coords->x, coords->y);
 	printf("Got target: %d\n", got_target);	
	ai_last_shot.x = coords->x;
	ai_last_shot.y = coords->y;
	return 1;
}

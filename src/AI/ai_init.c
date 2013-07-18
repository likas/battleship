#include "ai.h"

void ai_init()
{
	ai_cells_left = SIZE * SIZE;
	ai_last_shot.x = -1;
	ai_last_shot.y = -1;
	ai_last_shot_suc = -1;
	ai_last_shot_suc = -1;
	ai_direction.x = 0;
	ai_direction.y = 0;
	got_target = 0;
	ships = (int *)malloc(sizeof(int) * COUNT_SHIP);
	for(int i = 0; i < COUNT_SHIP; i++)
		ships[i] = COUNT_SHIP - i - 1;
}

#include "ai.h"

int ai_hit(COORDS coords)
{
	if(ai_player_field[coords.x][coords.y] == CELL_SHIP)	
		ai_player_field[coords.x][coords.y] = CELL_SHIP_FIRE;
	
}

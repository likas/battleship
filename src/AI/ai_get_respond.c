#include "ai.h"
void ai_mark_miss(int x, int y)
{
	if(ai_enemy_field[x][y] == CELL_NONE)
		ai_enemy_field[x][y] = CELL_MISS;
}

void ai_ship_mark_dead()
{
	COORDS coord = ai_last_shop;
    ai_direction.x *= -1;
	ai_direction.y *= -1;	
	do
	{
		ai_mark_miss(coord.x - 1, coord.y - 1);
		ai_mark_miss(coord.x    , coord.y - 1);
		ai_mark_miss(coord.x + 1, coord.y - 1);
		ai_mark_miss(coord.x + 1, coord.y    );
		ai_mark_miss(coord.x + 1, coord.y + 1);
		ai_mark_miss(coord.x    , coord.y + 1);
		ai_mark_miss(coord.x - 1, coord.y + 1);
		ai_mark_miss(coord.x - 1, coord.y + 1);
		coord.x += ai_direction.x;
		coord.y += ai_direction.y;
	}
	while(ai_enemy_field[coord.x][coord.y] == CELL_SHIP_FIRE);			
}

void ai_get_respond(enum _REQUESTS req)
{
     ai_enemy_field[ai_last_shot.x][ai_last_shot.y] = state;
 
     if( !got_target && state == REQ_HIT)
         got_target = 1;
     if( got_target && state == REQ_DESTROYED)
     {
         got_target = 0;
         ai_ship_mark_dead();
         ai_last_shot_suc.x = -1;
         ai_last_shot_suc.y = -1;
     }
 
     if( got_target )
         ai_choose_direction(state);
 
     if(state == REQ_HIT)
         ai_last_shot_suc = ai_last_shot;
}

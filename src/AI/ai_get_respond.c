#include "ai.h"

void ai_mark_miss(int x, int y)
{
	if(ai_enemy_field[x][y] == CELL_NONE)
		ai_enemy_field[x][y] = CELL_MISS, ai_cells_left--;
}

void ai_ship_mark_dead()
{
	COORDS coord = ai_last_shot;
    ai_direction.dx *= -1;
	ai_direction.dy *= -1;	
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
		coord.x += ai_direction.dx;
		coord.y += ai_direction.dy;
	}
	while(ai_enemy_field[coord.x][coord.y] == CELL_SHIP_FIRE);			
}

void ai_get_respond(enum _REQUESTS req)
{
	 enum _CELL_STATE state;
	 switch(req)
	 {
		case REQ_HIT:
			state = CELL_SHIP_FIRE;
			break;
		case REQ_MISS:
			state = CELL_MISS;
			break;
		case REQ_DESTROYED:
			state = CELL_SHIP_FIRE;
			break;
		default: 
			return; 
			break;
	 }
	 
 	 ai_enemy_field[ai_last_shot.x][ai_last_shot.y] = state;

     if( !got_target && req  == REQ_HIT)
         got_target = 1;
     if( got_target && req == REQ_DESTROYED)
     {
         got_target = 0;
         ai_ship_mark_dead();
         ai_last_shot_suc.x = -1;
         ai_last_shot_suc.y = -1;
     }
 
     if( got_target )
         ai_choose_direction(req);
 
     if(req == REQ_HIT)
         ai_last_shot_suc = ai_last_shot;
}

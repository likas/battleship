#include "ai.h"

void ai_mark_miss( int x, int y )
{
	if( ai_enemy_field[ x ][ y ] == CELL_NONE ) {
		ai_enemy_field[ x ][ y ] = CELL_MISS;
		ai_cells_left--;
	}
}

// Our Ai must be smart so if he kills the ship 
// he marks all cells around it with MISS state
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
	while( ai_enemy_field[ coord.x ][ coord.y ] == CELL_SHIP_FIRE );			
}

// AI bases his further actions on respond from client
void ai_get_respond( enum _REQUESTS req )
{
	 enum _CELL_STATE state;
	 switch( req ) {
		case REQ_HIT:
			printf( "Hit!\n" );
			state = CELL_SHIP_FIRE;
			break;
		case REQ_MISS:
			printf( "Miss!\n" );
			state = CELL_MISS;
			break;
		case REQ_DESTROYED:
			printf( "Destroyed ship!\n" );
			state = CELL_SHIP_FIRE;
			break;
		default: 
			printf( "Another %d\n", req );
			return; 
			break;
	 }
	 
	 printf("State %d\n", state); 
 	 
	 ai_enemy_field[ ai_last_shot.x ][ ai_last_shot.y ] = state;

     if( !got_target )
	 {
	 	if(req  == REQ_HIT) 
        	got_target = 1, ai_choose_direction(req);
 	 } 
	 else 
	 {
		if(req == REQ_HIT)
			got_target = 2; 
		if(req == REQ_MISS)
	 		ai_choose_direction(req);
	 }
	 if( req == REQ_DESTROYED)
     {
         got_target = 0;
         ai_ship_mark_dead();
         ai_last_shot_suc.x = -1;
         ai_last_shot_suc.y = -1;
     }
 
     if( req == REQ_HIT ) 
	 {
         ai_last_shot_suc = ai_last_shot;
	 }
}

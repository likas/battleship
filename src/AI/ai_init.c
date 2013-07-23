#include "ai.h"

// Before AI starts playing with client 
// he must get ready for it
void ai_init()
{
	ai_ship_count = 10;
	ai_last_shot.x = -1;
	ai_last_shot.y = -1;
	ai_last_shot_suc.x = -1;
	ai_last_shot_suc.y = -1;
	ai_direction.dx = 0;
	ai_direction.dy = 0;
	got_target = 0;
	ships = (int *)malloc( sizeof( int ) * COUNT_SHIP );
	for ( int i = 0; i < COUNT_SHIP; i++ ) {
		ships[ i ] = COUNT_SHIP - i;
	}
	
	ai_player_field = calloc( SIZE, sizeof( int* ) );
	for ( int index = 0; index < SIZE; index++ ) {
		ai_player_field[ index ] = calloc( SIZE, sizeof( int ) );
	}	
	
	ai_enemy_field = calloc( SIZE, sizeof( int* ) );
	for ( int index = 0; index < SIZE; index++ ) {
		ai_enemy_field[ index ] = calloc( SIZE, sizeof( int ) );
	}	
}

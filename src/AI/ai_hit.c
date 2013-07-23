#include "ai.h"

int is_ship_dead( int**, COORDS, int );
void choose_direction( int**, COORDS, AI_DIRECTION* );
void kill_the_ship( int, int );
int is_game_ended( int );
int who_won( int );
int is_next_cell_valid( int**, COORDS, AI_DIRECTION* );

int ai_hit( int** field, COORDS coords, int whos_been_hit )
{
	int ret_status = -1;
	
	// If the ship is hit
	if ( field[ coords.x ][ coords.y ] == CELL_SHIP ) {	
		field[ coords.x ][ coords.y ] = CELL_SHIP_FIRE;

		if ( is_ship_dead( field, coords, whos_been_hit ) ) {
			if ( is_game_ended( whos_been_hit ) ) {
				ret_status = who_won( whos_been_hit );
			} else {
				ret_status = REQ_DESTROYED;
			}
		} else {
			ret_status = REQ_HIT;
		}
		return ret_status;
	}
	
	// If missed
	if ( field[ coords.x ][ coords.y ] == CELL_NONE ) {
		field[ coords.x ][ coords.y ] = CELL_MISS;

		ret_status = REQ_MISS;
		return ret_status;
	}
	
	return ret_status;
}



int is_ship_dead( int** field, COORDS coords, int who )
{
	int ship_size = 0;
	AI_DIRECTION direction;
	COORDS start_position = coords;
	
	choose_direction( field, coords, &direction );
	if ( direction.dx == 0 && direction.dy == 0 ) {
		ship_size = 1;
		kill_the_ship( who, ship_size );
		return 1;
	}
	
	// Forward check
	do {
		
		++ship_size;
		coords.x += direction.dx;
		coords.y += direction.dy;
		if ( coords.x >= SIZE || coords.x < 0 ||
			 coords.y >= SIZE || coords.y < 0 ) {
			break;
		}
		
		if ( field[ coords.x ][ coords.y ] == CELL_SHIP ) {
			return 0;
		}
	} while ( field[ coords.x ][ coords.y ] != CELL_NONE  &&
			 field[ coords.x ][ coords.y ] != CELL_MISS );
	
	// Backward check
	direction.dx *= -1;
	direction.dy *= -1;
	coords.x = start_position.x + direction.dx;
	coords.y = start_position.y + direction.dy;
	if ( coords.x >= SIZE || coords.x < 0 ||
		 coords.y >= SIZE || coords.y < 0 ) {
		kill_the_ship( who, ship_size );
		return 1;
	}

	while ( field[ coords.x ][ coords.y ] != CELL_NONE  &&
			field[ coords.x ][ coords.y ] != CELL_MISS ) {
		if ( field[ coords.x ][ coords.y ] == CELL_SHIP ) {
			return 0;
		}	
		++ship_size;

		coords.x += direction.dx;
		coords.y += direction.dy;
		if ( coords.x >= SIZE || coords.x < 0 ||
			 coords.y >= SIZE || coords.y < 0 ) {
			break;
		}
	}
	
	kill_the_ship( who, ship_size );
	return 1;
}
	


void choose_direction( int** field, COORDS coords, AI_DIRECTION* direction )
{
	direction->dx = 1;
	direction->dy = 0;

	if ( !is_next_cell_valid( field, coords, direction ) ) {
		direction->dx = -1;
		direction->dy = 0;
	} else {
		return;
	}

	if ( !is_next_cell_valid( field, coords, direction ) ) {
		direction->dx = 0;
		direction->dy = 1;
	} else {
		return;
	}

	if ( !is_next_cell_valid( field, coords, direction ) ) {
		direction->dx = 0;
		direction->dy = -1;
	} else {
		return;
	}
	
	if ( !is_next_cell_valid( field, coords, direction ) ) {
		direction->dx = 0;
		direction->dy = 0;
	} else {
		return;
	}
}


int is_next_cell_valid( int** field, COORDS coords, AI_DIRECTION* direction )
{
	if ( ( ( coords.x + direction->dx ) < SIZE  && ( coords.x + direction->dx ) > -1 ) &&
		 ( ( coords.y + direction->dy ) < SIZE  && ( coords.y + direction->dy ) > -1 ) &&
		 ( field[ coords.x + direction->dx ][ coords.y + direction->dy ] == CELL_SHIP  ||
		 field[ coords.x + direction->dx ][ coords.y + direction->dy ] == CELL_SHIP_FIRE ) ) {
		return 1;
	}
	return 0;
}	



void kill_the_ship( int who, int ship_size )
{
	if ( who == AI ) {
		ai_ship_count--;
	}

	if ( who == PLAYER ) {
		ships[ ship_size - 1 ]--;
	}
}



int is_game_ended( int who )
{
	if ( who == AI ) {
		if ( ai_ship_count == 0 ) {
			return 1;
		} else {
			return 0;
		}
	}

	if ( who == PLAYER ) {
		for ( int ship_size = 0; ship_size < COUNT_SHIP; ship_size++ ) {
			if ( ships[ ship_size ] > 0 ) {
				return 0;
			}
		}
		return 1;
	} 
	
	return 0;
}



int who_won( int who )
{
	if ( who == PLAYER ) {
		return REQ_YOULOSE;
	}

	if ( who == AI ) {
		return REQ_YOUWIN;
	}

	return REQ_DISCONNECT;
}

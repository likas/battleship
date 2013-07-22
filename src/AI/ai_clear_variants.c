#include "ai.h"

void fill_gaps( int **, int, int, int, int );
int vert_ship_can_fit( int**, int, int, int );

// pocedure which analyzes the field and marks places 
// where no more ships can be located at this state of the game
// 
// NOTE: this thing is completely experimental 
// but may make our AI much smarter 
void ai_clear_variants( int **ai_emeny_field )
{
	int blank_cells_cnt = 0;
	int ship_min_length = 1;
	int row;
	int coll;
	
	// seeking for the smallest size amoung ships which are still in game 
	while ( ship_min_length < COUNT_SHIP ) {
		if ( ships[ ship_min_length ] == 0 )
			ship_min_length++;
		else 
			break;
	}

	if (ship_min_length == 1) 
		return;
	
	for ( row = 0; row < SIZE; row++) {
		blank_cells_cnt = 0;
		for ( coll = 0; coll < SIZE; coll++ ) {
			if ( ai_enemy_field[ row ][ coll ] != CELL_NONE ) {
				if ( blank_cells_cnt < ship_min_length ) {
					fill_gaps(ai_enemy_field, row, coll - 1, blank_cells_cnt, ship_min_length );	
				blank_cells_cnt = 0;
				}
			}
			blank_cells_cnt++;
		}
	}
}

// this one does the marking part 
void fill_gaps( int** ai_enemy_field, int row, int coll, int blank_cells_cnt, int ship_min_length )
{
	int pos_x = coll;
	int pos_y = row;
	int blanks = blank_cells_cnt;
	do {
		if( !vert_ship_can_fit( ai_enemy_field, pos_x, pos_y, ship_min_length ) ) {
			ai_enemy_field[ pos_x ][ pos_y ] = CELL_MISS;
			ai_cells_left--;
		}
		pos_x--;
	} while (blanks != 0);
}	

// this function helps AI decide if a ship could occur in the current cell 
int vert_ship_can_fit( int** ai_enemy_field, int start_pos_x, int start_pos_y, int ship_min_length )
{
	int blanks;
	int pos_y;

	for ( pos_y = start_pos_y, blanks = 0; pos_y < SIZE; pos_y++) {
		if ( ai_enemy_field[ start_pos_x ][ pos_y ] != CELL_NONE ) {
			if ( blanks < ship_min_length ) {
				break;
			} else {
				return 1;
			}
		}
		blanks++;
	}
	
	for ( pos_y = start_pos_y - 1; pos_y >= 0; pos_y-- ) {
		if ( ai_enemy_field[ start_pos_x ][ pos_y ] != CELL_NONE ) {
			if ( blanks < ship_min_length ) {
				return 0;
			} else {
				return 1;
			}
		}
		blanks++;
	}
	return 1;
}

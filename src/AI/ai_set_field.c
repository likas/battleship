#include "ai.h"

// AI must know where are the ships on the player field 
// so he could chek for successful shots
int ai_set_field( int **field )
{
	if( field == NULL ) {
		return 0;
	}
	player_field = field;
	return 1;
}

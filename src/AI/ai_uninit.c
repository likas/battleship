#include "ai.h"

// Releasing all resources taken when the game is over
void ai_uninit()
{
	free( ships );
	for ( int index = 0; index < SIZE; index++ ) {
		free( ai_enemy_field[ index ] );
		free( ai_player_field[ index ] );
	}
	free( ai_enemy_field );
	free( ai_player_field );
}

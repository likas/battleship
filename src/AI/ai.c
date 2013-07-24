// This module emulates clients interaction with other client through server
// you ask him - he answers. Yay!

#include "ai.h"

message ai( message msg )
{
	message answer;
	COORDS coords;

	switch( msg.command ) {
		case MSG_SG:
			ai_init();
			if ( ai_rand_matr( ai_player_field ) != 0 ) {
				answer.command = REQ_DISCONNECT;
				answer.params[ 0 ] = 'm';
				return answer;
			}
			if( ( ( double )rand() / RAND_MAX ) > 0.5)
			{
				answer.command = MSG_SG;
				answer.params[ 0 ] = 'f';
				return answer;
			}
			else
			{
				answer.command = MSG_SG;
				answer.params[ 0 ] = 's';
				return answer;
			}
			break;
		case MSG_HM:
			ai_shoot( &coords );
			answer.command = ai_hit( player_field, coords, PLAYER );
			coords_atoi( answer.params, coords );

			if ( answer.command == REQ_YOULOSE ||
				 answer.command == REQ_YOUWIN ) {
				ai_uninit();
				return answer;
			}

			ai_get_respond( answer.command );
			//ai_clear_variants( ai_enemy_field );
			return answer;
			break;
		case MSG_AT:
			coords_itoa( msg.params, &coords );
			answer.command = ai_hit( ai_player_field, coords, ENEMY);
			if ( answer.command == REQ_YOULOSE ||
				 answer.command == REQ_YOUWIN ) {
				ai_uninit();
			}
			return answer;
			break;
		default:
			answer.command = REQ_DISCONNECT;
			return answer;
			break;
	}
}

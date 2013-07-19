//This module emulation server and apponent clisent
#include "ai.h"

message ai(message msg)
{
	message answer;
	COORDS coords;

	switch( msg.command ) {
		case MSG_SG:
			ai_init();
			if((double)rand()/RAND_MAX > 0.5)
			{
				answer.command = MSG_SG;
				answer.params[0] = 'f';
				return answer;
			}
			else
			{
				answer.command = MSG_SG;
				answer.params[0] = 's';
				return answer;
			}
		case MSG_HM:
			ai_shoot( &coords );
			answer.command = ai_hit( player_field, coords, PLAYER );
			coords_atoi( answer.params, coords );
			return answer;
			break;
		case MSG_AT:
			coords_itoa( msg.params, &coords );
			answer.command = ai_hit( ai_player_field, coords, AI );
			return answer;
			break;
		default:
			answer.commnad = REQ_DISCONNECT;
			return answer;
			break;
	}
}

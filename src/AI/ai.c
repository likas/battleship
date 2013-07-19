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
			break;
		case MSG_HM:
			ai_shoot( &coords );
			//answer.command = check_hit(); <- take from server
			coords_atoi( answer.params, coords );
			return answer;
			break;
		case MSG_AT:
			coords_itoa( msg.param, &coords );
			answer.command = ai_hit( coords );
			answer.params = "";
			return answer;
			break;
		default:
			answer.commnad = REQ_DISCONNECT;
			answer.params = "AI: Don't know how to respond, sorry.\n";
			return answer;
			break;
	}
}

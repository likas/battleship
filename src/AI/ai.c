//This module emulation server and apponent clisent
#include "ai.h"

int bot_step; //1 if step Ai 
message ai(message msg)
{
	message answer;
	switch( msg.command )
	{
		case MSG_SG:
			ai_init();
			if((double)rand()/RAND_MAX > 0.5)
			{
				bot_step = 0;
				answer.command = MSG_SG;
				answer.params[0] = 'f';
				return answer;
			}
			else
			{
				bot_step = 1;
				answer.command = MSG_SG;
				answer.params[0] = 's';
				return answer;
			}
		case MSG_AT:
	}
}

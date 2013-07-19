#include "client.h"

int client_send_text(int action; char* text){
	message	msg; /* struct message{ int command, char* params[128] }
	/* @ FIELD_START FIELD_END @ */
	msg.command=action; /* type of message: chat message: NN, TT, SG */
	if(action==MSG_SG){
		
	}
	sscanf(text,"%s",msg.params); /* copying parameters to the message
								   * structure */
	if (send(TUNNEL, msg, sizeof(msg),0)!=sizeof(msg)) /* TUNNEL is global 
														* and attach to socket
														* we send messages to */
	{
		return 1;
	}
	return 0;
}

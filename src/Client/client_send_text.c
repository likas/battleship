/* #include "client.h" */
#include <stdio.h>
#include "../mboi.h"
extern int GAME_TUNNEL;
int client_send_text(int action, char* text){
	printf("%s\n", __func__);
	printf("action: %d\n", action);
	printf("message: %s\n", text);
//	getch();
//	printf("T: %d\n", GAME_TUNNEL); 
	message	msg; /* struct message{ int command, char* params[128] } */
	int check;
	/* @ FIELD_START FIELD_END @ */
	msg.command=action; /* type of message: chat message: NN, TT, SG */
	if((action == MSG_RL) || (action == MSG_SF)){
		
	} else if (action == MSG_SG) {
//		strcpy(msg.params, text)
		msg.params[0] = *text;
	} else {
		sscanf(text,"%s",msg.params); /* copying parameters to the message
								   * structure */
	}
	check=send(GAME_TUNNEL, (message*)&msg, sizeof(message),0); /* TUNNEL is global 
														* and attach to socket
														* we send messages to */
	printf("%d=%d\n", check, sizeof(message));
	if(check!=sizeof(message)){
		perror("send");
		exit(1);
		return 1;
	}
	return 0;
}

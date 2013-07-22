/* #include "../mboi.h" */
#include "client.h"
extern int TUNNEL;
int client_send_attack(COORDS xy){
	message msg;
	msg.command=MSG_AT;
	coords_atoi(msg.params, xy);
	if (send(TUNNEL, &msg, sizeof(msg),0)!=sizeof(msg)){
		return 1;
	}
	return 0;
}

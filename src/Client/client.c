#include "client.h"
#define YOURMOVE 0
int TUNNEL=0, GAME_TUNNEL=0;
struct sockaddr_in 
int main(){
	char player_id=-1;
	gui();
	/*here lies gui_init(). it gives control to us when user input his name 
	* when the name is placed, we shall send it to server?
	* with no idea how... */
	TUNNEL=socket_init(); /* TUNNEL is lying somewhere in the header, ask
						   * someone else, what do you want from me, for
						   * Christ sake?! */
	/*here is something like: */
	client_send_text(MSG_NN, nickname);
	/*there we send a NN located in nickname global which is defined in gui.h
	* to the server with TUNNEL established earlier */
	/*here server shall send us a list of existing games, and we get it like: */
	mesaage received;
	while(){
			if(recv(TUNNEL, &received, sizeof(message), 0) > 0){
				break;
			}}
	switch(received.command){
		case REQ_STARTLIST:
			player_id=(char)go_list(); /* callin' ant_player_list(usn, len) inside,
						* and it returns number of player's structure
						* which is converted to player's id and returned */ 
			break;
		case DECLINE:
			printf("An error occured: server return DECLINE\n");
			exit(1);
			break;
		default:
			printf("An error occurred: Error while receiving player list");
			exit(1);
			break;
	}
	/* sending a player id; getting socket for new game instead */
	client_send_text(MSG_SG, &player_id);
	while(){
			if(recv(TUNNEL, &received, sizeof(message), 0) > 0){
				break;
			}}
	/* getting socket from server */
	/* here we go: have a socket for game; next received message will be about who
	* plays first */
	while(){
		if(recv(GAME_TUNNEL, &received, sizeof(message), 0) > 0){
			break;
		}
	}

	if(received.command==MSG_RQ && (*(received.params)=='f'||*(received.params)=='s')){
		YOURMOVE=(*(received.params)=='f')?1:0;
	}else{
		printf("An error occurred: receive that: '%s' kinda crap instead of f/s move\n", received.params);
	}
	/* had a move queue */
	/* can start a game cycle */
	
}








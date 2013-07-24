#include "../mboi.h"
#include "client.h"
#include <stdio.h>

/* GLOBALS */
pthread_t chat_thread;
/* struct sockaddr_in  */

int main(int argc, char* argv[]){
	int WOL=-1;
	srand(time(NULL));
	if(argc==1){
		printf("Input 1 as a parameter to play with AI, 2 for another user\n");
		exit(1);
	}else{
		ONLINE=(*argv[1]=='1')?0:1;
	}
	/*here lies gui_init(). it gives control to us when user input his name 
	* when the name is placed, we shall send it to server?
	* with no idea how... */
	gui();
	map_init();
	
	if(!ONLINE){
		/* possibly init*/
		WOL=with_ai();
		
		endgui(WOL);
		/* message */
	}else{
	char player_id=-1;
	message received;
	COORDS xy; xy.x=-1; xy.y=-1;
	GAME_TUNNEL=socket_init(); /* TUNNEL is lying somewhere in the header, ask
						   * someone else, what do you want from me, for
						   * Christ sake?! */
	/*here is something like: */
	/*there we send a NN located in nickname global which is defined in gui.h
	* to the server with TUNNEL established earlier */
	/*here server shall send us a list of existing games, and we get it like: */
	while(1){
			if(recv(GAME_TUNNEL, &received, sizeof(message), 0) > 0){
				break;
			}}
	switch(received.command){
		case REQ_STARTLIST:
			player_id=(char)go_list(); /* callin' ant_player_list(usn, len) inside,
						* and it returns number of player's structure
						* which is converted to player's id and returned */ 
			break;
		case REQ_DECLINE:
			printf("An error occured: server return DECLINE\n");
			exit(1);
			break;
		default:
			printf("An error occurred: Error while receiving player list");
			exit(1);
			break;
	}
	/* sending a player id; getting socket for new game instead */
	if(player_id>0){ /* if player's list isnt empty */
		client_send_text(MSG_SG, &player_id); /* we send choosed player's id */
	}
	while(1){
			if(recv(GAME_TUNNEL, &received, sizeof(message), 0) > 0){
				break;
			}}
	/* and waiting socket from server, no matter are we first or second */
	TUNNEL=GAME_TUNNEL;
	GAME_TUNNEL=received.command;
	/* set ships here */
	/* TODO set ships here, init map (here?) im thinking about 'init' first, then passing fields to set up ships
	* as parameters */
	/* sending a gamefield */
	send(GAME_TUNNEL, SMAP, (sizeof(int)*100), 0);
	/* here we go: have a socket for game; next received message will be about who
	* plays first */
	while(1){
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
	/* !TODO! thread */
	/* создаем треду */
	/* if((pthread_create(&chat_tread, NULL, &waiting, NULL)) < 0){  at this moment, we watch all messages 
		perror("thread create");								  from server, no matter what we also do 
		exit(1);
	}*/
	while(received.command!=REQ_YOUWIN || received.command!=REQ_YOULOSE){
		if(YOURMOVE){
			xy=De_Move(EMAP);
			client_send_attack(xy);
		}else{
			while(1){
				if(recv(GAME_TUNNEL, &received, sizeof(message), 0) > 0){
				break;
				}
			}
			/* и обработка принятого */
			switch(received.command){
				case REQ_DISCONNECT: /* done */
					printf("Your partner suddenly disconnected. Game over\n");
					exit(1);
					break;
				case MSG_TT: /* done */
					GUICHATLEN=FINchat(opname, received.params, GUICHATLEN);
					break;
				case REQ_YOUWIN: /* done */
					WOL=1;
					break;
				case REQ_YOULOSE: /* done */
					WOL=0;
					break;
				case MSG_AT:
					/*COORDS*/coords_itoa(received.params, &xy);
					while(1){
						if(recv(GAME_TUNNEL, &received, sizeof(message), 0) > 0){
							break;
						}
					}
					if(received.command==REQ_MISS){ YOURMOVE=1; }
					/* перерисовываем свою! ячейку */
					SMAP[xy.x][xy.y]=received.command; /* записываем локально */
					FINchcell(xy.x, xy.y, received.command, 0); /* рисуем в GUI */
					break;
				case REQ_HIT:
					/* перерисовать карту противника на хит */
					EMAP[xy.x][xy.y]=received.command; /* записываем локально */
					FINchcell(xy.x, xy.y, received.command, 1); /* рисуем в GUI */
					break;
				case REQ_MISS:
					/* перерисовать карту противника на промах */
					EMAP[xy.x][xy.y]=received.command; /* записываем локально */
					FINchcell(xy.x, xy.y, received.command, 1); /* рисуем в GUI */
					break;
				case REQ_DESTROYED:
					/* перерисовать карту противника на хит */
					EMAP[xy.x][xy.y]=REQ_HIT; /* записываем локально */
					FINchcell(xy.x, xy.y, REQ_HIT, 1); /* рисуем в GUI */

					/* вывести в чат уничтожение */
					GUICHATLEN=FINchat("server\0", "Ship is fully destroyed!\n\0" , GUICHATLEN);
					break;
				default:
					break;
			}
			}
		} /* for game cycle */
	GAME_TUNNEL=TUNNEL;




	}/* this is for }else{ of ONLINE */
	
	return 0;
}





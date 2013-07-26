#include "../mboi.h"
#include "client.h"
#include <stdio.h>

/* GLOBALS */
pthread_t chat_thread;
/* struct sockaddr_in  */

int main(int argc, char* argv[]){
	int WOL=-1;
	message sent;
	srand(time(NULL));
	/*here lies gui_init(). it gives control to us when user input his name 
	* when the name is placed, we shall send it to server?
	* with no idea how... */
	gui();
	if(MODEFLAG == QUIT)
		return;
	map_init();
	if(MODEFLAG >> 1) //Game with ai
	{
		/* possibly init*/
		WOL=with_ai(MODEFLAG & 1);
		getch();		
		endgui(WOL);
	}
	else //Game with other client
	{
	char player_id=-1;
	message received;
	COORDS xy; xy.x=-1; xy.y=-1;
	/*GAME_TUNNEL=socket_init(); */ /* TUNNEL is lying somewhere in the header, ask
						   * someone else, what do you want from me, for
						   * Christ sake?! */
	struct sockaddr_in addr;
	GAME_TUNNEL=socket(AF_INET, SOCK_STREAM, 0);
	if(GAME_TUNNEL<0){
		perror("socket");
		exit(1);
	}
	addr.sin_family=AF_INET;
	
	if (argc > 1) {
		addr.sin_port=htons(atoi(argv[1]));
	} else {
		addr.sin_port=htons(1999);
	}
/*inet_aton("127.0.0.1", &addr.sin_addr); */
/* 	inet_pton(AF_INET, "156.13.2.25", &addr.sin_addr); */
/* 	inet_pton(AF_INET, "192.168.3.1", &addr.sin_addr); */
 	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if(connect(GAME_TUNNEL, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		perror("connect");
		exit(1);
	}
	/*here is something like: */
	/*there we send a NN located in nickname global which is defined in gui.h
	* to the server with TUNNEL established earlier */
	/*here server shall send us a list of existing games, and we get it like: */
	if((client_send_text(40, username))>0){
		printf("Somethin' glitched during process of sending NN\n");
		exit(1);
	}
	while(player_id==-1){
	if((client_send_text(MSG_RL, (char*)0))!=0){ /* sending MSG_RL */
		printf("client_send_text return an error\n");
		exit(1);
	}
		while(1){ /* receiving answer */
				if(recv(GAME_TUNNEL, &received, sizeof(message), 0) > 0){
					break;
				}}
		switch(received.command){ /* it can be as below: */
			case REQ_STARTLIST: /* it's for getting/updating player's list */
				player_id=go_list(); /* callin' ant_player_list(usn, len) inside,
							* and it returns number of player's structure
							* which is converted to player's id and returned, OR
							* OR -1 in case of chosing new game */ 
				break;
			case REQ_DECLINE: /* it's for case of error */
				printf("An error occured: server return DECLINE\n");
				exit(1);
				break;
			case REQ_GAMESTARTED: /* it's when someone pick our player as an opponent */
				
				player_id=-2; /* to exit waiting cycle */
				break;
			default:
				printf("An error occurred: Error while receiving player list\n");
				exit(1);
				break;
		}

		if(player_id>=0){ /* /отправляем номер, если мы сами его выбрали */
			client_send_text(MSG_SG, &player_id); /* we send choosed player's id */
		/* waiting for response */
		while(1){
			if(recv(GAME_TUNNEL, &received, sizeof(message), 0) > 0){
				break;
			}
		}
		if(received.command==REQ_DECLINE){
			/* if it's DECLINE answer, we have to start again with that while() staff, */
			player_id=-1;
			printf("DECLINE\n");
//			getch();
		}else if(received.command==REQ_ACCEPT){
			printf("accept\n");
//			getch();
			/* if ACCEPT, we can send a map, т.е. out from cycle */
			break;
		}else if(received.command == REQ_GAMESTARTED)
		{
			break;
		}else
		{
		    printf("Something unexpected just arrived instead\n of ACCEPT, or DECLINE. Exiting...\n"); exit(1); 
		}
		}
	} /* end of 'while(player_id..)'
	 здесь мы окажемся, если: 1) пришло GAMESTARTED 2) мы выбрали игрока, с которым хотим играть */
	/* set ships here */
	if(MODEFLAG & 1) { //Manual field or random
		De_Init(SMAP, EMAP);
        ras(SMAP);
	} else {
        ai_rand_matr(SMAP);
		De_Init(SMAP, EMAP);
	}
	/* sendiing a gamefield */
	client_send_text(MSG_SF, 0);
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
			/* TODO if -1;-1 : exit */
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




	}/* this is for }else{ of ONLINE */
	
	return 0;
}





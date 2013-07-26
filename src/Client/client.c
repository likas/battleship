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
	if(MODEFLAG == QUIT) {
	    endgui(3);
		exit(0);
	}
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
	struct sockaddr_in addr;
	GAME_TUNNEL=socket(AF_INET, SOCK_STREAM, 0);
	if(GAME_TUNNEL<0){
		perror("socket");
		exit(1);
	}
	addr.sin_family=AF_INET;
	if (argc > 1) {
		addr.sin_port=htons(atoi(argv[1]));
		if (argc > 2) {
			inet_pton(AF_INET, argv[2], &addr.sin_addr);
		}
	} else {
		addr.sin_port=htons(1999);
	}
//<<<<<<< HEAD
/* 	inet_pton(AF_INET, "156.13.2.25", &addr.sin_addr); */
/* 	inet_pton(AF_INET, "192.168.3.1", &addr.sin_addr); */
// 	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
//=======
// 	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
//>>>>>>> 829be288723f1cbdddd82aeb085b89333817e783
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
		//		sleep(1000);
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
			player_id=-1;
		}else if(received.command==REQ_ACCEPT){
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
		FINref(stdscr,1,0);
        ai_rand_matr(SMAP);
		De_Init(SMAP, EMAP);
	}
	/* sendiing a gamefield */
	client_send_text(MSG_SF, 0);
	for(int i = 0; i < SIZE; i++)
		send(GAME_TUNNEL, SMAP[i], (sizeof(int)*SIZE), 0);
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
	if (YOURMOVE)
		guiturn(PLAYER,NULL);
	else
		guiturn(ENEMY,NULL);
	
		do{
		if(YOURMOVE){
			do
			{
				xy=De_Move(EMAP);
				
				if(xy.x == -1 && xy.y == -1)
				{
					client_send_text(REQ_DISCONNECT, "Blobloblo");
					WOL = REQ_DISCONNECT;
					break;
				}
			}while(EMAP[xy.x][xy.y] != CELL_NONE );
			
				
			if(xy.x != -1 && xy.y != -1)
				client_send_attack(xy);
			else
				break;
		}
			if(recv(GAME_TUNNEL, &received, sizeof(message), 0) < 0){
				WOL = REQ_DISCONNECT;	
				break;
				}
			/* и обработка принятого */
			switch(received.command){
				case REQ_DISCONNECT: /* done */
					WOL = REQ_NDISCONNECT;
					endgui(WOL);
					map_deinit();
					break;
				case MSG_TT: /* done */
					GUICHATLEN=FINchat(opname, received.params, GUICHATLEN);
					break;
				case REQ_YOUWIN: /* done */
					WOL=REQ_YOUWIN; 
					endgui(WOL);
					map_deinit();
					break;
				case REQ_YOULOSE: /* done */
					WOL=REQ_YOULOSE;
					endgui(WOL);
					map_deinit();
					break;
				case REQ_HIT:
					/* перерисовать карту противника на хит */
					coords_itoa(received.params, &xy);
					if(YOURMOVE)
						EMAP[xy.x][xy.y]= CELL_SHIP_FIRE, /* записываем локально */
						FINchcell(xy.x, xy.y, CELL_SHIP_FIRE, 1), /* рисуем в GUI */
						guiturn(PLAYER,REQ_HIT);
					else
						SMAP[xy.x][xy.y]= CELL_SHIP_FIRE, /* записываем локально */
						guiturn(ENEMY,REQ_HIT),
						FINchcell(xy.x, xy.y, CELL_SHIP_FIRE, 0); /* рисуем в GUI */
					break;
				case REQ_MISS:
					/* перерисовать карту противника на промах */
					coords_itoa(received.params, &xy);
					if(YOURMOVE)
						EMAP[xy.x][xy.y]= CELL_MISS, /* записываем локально */
						FINchcell(xy.x, xy.y, CELL_MISS, 1), /* рисуем в GUI */
						guiturn(PLAYER,REQ_MISS);
					else
						SMAP[xy.x][xy.y]= CELL_MISS, /* записываем локально */
						FINchcell(xy.x, xy.y, CELL_MISS, 0); /* рисуем в GUI */
						guiturn(ENEMY,REQ_MISS);	
					YOURMOVE =! YOURMOVE;
					break;
				case REQ_DESTROYED:
					/* перерисовать карту противника на хит */
					coords_itoa(received.params, &xy);
					if(YOURMOVE)
						EMAP[xy.x][xy.y]= CELL_SHIP_FIRE, /* записываем локально */
						round_ship(EMAP,xy.x,xy.y),
					/* вывести в чат уничтожение */
						guiturn(PLAYER,REQ_DESTROYED);
					else
						{
						SMAP[xy.x][xy.y]= CELL_SHIP_FIRE; /* записываем локально */
						guiturn(ENEMY,REQ_DESTROYED);
						}
					/* вывести в чат уничтожение */
					render(SMAP,EMAP,1);
					break;
				default:
					endgui(REQ_DISCONNECT);
					map_deinit();
					break;
			}
		} /* for game cycle */
		while(received.command!=REQ_DISCONNECT && received.command!=REQ_YOUWIN && received.command!=REQ_YOULOSE );
	}/* this is for else of ONLINE */
	
	endgui(WOL);
//	map_deinit();
	return 0;
}

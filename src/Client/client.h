#ifndef CLIENT_H
#define CLIENT_H
/*----------------------*/
/* #define size 10 */
/*----------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "../mboi.h"
#include "../AI/ai.h" 
#include "../GUI/gui.h"
/*----------------------*/

int ser_soc;
int **SMAP;
int **EMAP;
int TUNNEL;
int GAME_TUNNEL;
int YOURMOVE;
int ONLINE;
/*----------------------*/

int coords_atoi(char *, COORDS);
int coords_itoa(char *, COORDS*);
int client_send_attack(COORDS xy);
int client_send_text(int action, char* text);
int gameover(int *smap);
int shoot(int* smap, COORDS a);
int killed(int x, int y);
int socket_init();
int go_list();
int parser_itoa(int number, char* buf);
int with_ai(); 

/*----------------------*/
void map_init();
void map_deinit();
#endif

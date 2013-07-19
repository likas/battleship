#ifndef AI_H
#define AI_H
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "../mboi.h"
#include "../Client/client.h"
typedef struct _AI_DIRECTION
{
	int dx; 
	int dy;
} AI_DIRECTION;

enum _GAMERS 
{
  AI,
  PLAYER
} GAMERS;

int ai_ship_count = 10; 
int ai_cells_left; //Count unshoot cells
int **ai_player_field, **ai_enemy_field, **player_field;
COORDS ai_last_shot;
COORDS ai_last_shot_suc;
AI_DIRECTION ai_direction;
int got_target;
int *ships;

//****Использовать извне и получать выгоду***
message ai(message);
enum _REQUESTS ai_hit(COORDS);
int ai_set_field(int **); //Set player field
void ai_init();    //Initialization library
void ai_uninit();  //Clean library from memory

//**** Module function *****
int ai_shoot(COORDS *coords); 
void ai_get_respond(enum _REQUESTS); 
void ai_clear_variants(int **);			// marks places where no more ships can be located 
void ai_choose_direction(enum _REQUESTS);
void ai_rand_cell(int **, COORDS *);
int ai_rand_matr(int **);
void ai_draw(int **, int**);
#endif 

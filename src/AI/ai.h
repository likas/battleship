#ifndef AI_H
#define AI_H
#include <sys/time.h>
#include <time.h>
#include "../mboi.h"

typedef struct _AI_DIRECTION
{
	int dx; 
	int dy;
} AI_DIRECTION;

int ai_cells_left; //Count unshoot cells
int **ai_player_field, **ai_enemy_field, **player_field;
COORDS ai_last_shot;
COORDS ai_last_shot_suc;
AI_DIRECTION ai_direction;
int got_target;
int *ships;

//****Использовать извне и получать выгоду***
int ai(int x, int y);
void ai_init();    //Initialization library
void ai_uninit();  //Clean library from memory

//**** Module function *****
int ai_set_field(int **);
int ai_shoot(COORDS *coords);
int ai_hit(COORDS);
void ai_clear_variants(int **);			// marks places where no more ships can be located 
void ai_get_respond(enum _CELL_STATE);
void ai_choose_direction();
void ai_rand_cell(int **, COORDS *);

#endif 

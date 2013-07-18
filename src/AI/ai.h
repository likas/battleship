#ifndef AI_H
#define AI_H
#include <sys/time.h>
#include <time.h>
#include "../mboi.h"
int ai_cells_left = 100; //Count unshoot cells
int **ai_player_field, **ai_enemy_field, **player_field;

typedef struct _AI_DIRECTION
{
	int dx; 
	int dy;
} AI_DIRECTION;

int ai_set_field(int **);
int ai_shoot(COORDS *coords);
int ai_hit(COORDS);
void ai_get_respond(enum _CELL_STATE);
void ai_choose_direction();
void ai_ship_mark_dead();
void ai_rand_cell(int **, COORDS *);

#endif 

#ifndef AI_H
#define AI_H
#include <sys/time.h>
#include <time.h>
#include "../mboi.h"

int ai_cells_left = SIZE * SIZE; //Count unshoot cells
int **ai_player_field, **ai_enemy_field, **player_field;
COORDS ai_last_shot = {-1, -1};
COORDS ai_last_shot_suc = {-1, -1};
AI_DIRECTION ai_direction = {0, 0};
int got_target = 0;
int ships[COUNT_SHIP] = {4, 3, 2, 1};

typedef struct _AI_DIRECTION
{
	int dx; 
	int dy;
} AI_DIRECTION;

void ai_init();
int ai_set_field(int **);
int ai_shoot(COORDS *coords);
int ai_hit(COORDS);
void ai_clear_variants();
void ai_get_respond(enum _CELL_STATE);
void ai_choose_direction();
void ai_ship_mark_dead();
void ai_rand_cell(int **, COORDS *);

#endif 

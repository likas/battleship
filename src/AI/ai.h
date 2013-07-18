#pragma once
#include <sys/time.h>
#include <time.h>
int ai_cells_left = 100; //Count unshoot cells
int **ai_player_field, **ai_enemy_field, **player_field;

typedef struct _AI_DIRECTION
{
	int dx; 
	int dy;
} AI_DIRECTION;

typedef struct _AI_COORDS
{
	int x;
	int y;
} AI_COORDS;

int ai_set_field(int **);
int ai_shoot(COORDS *coords);
int ai_hit(COORDS);
void ai_get_respond(int);
void ai_choose_direction();
void ai_ship_mark_dead();
void ai_rand_cell(int **, AI_COORDS *);


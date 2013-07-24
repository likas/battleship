#ifndef AI_H
#define AI_H
#include <stdio.h>
#include "../mboi.h"
#include "../Client/client.h"

// AI Data structures

// Used in ai_rand_matr() to define 
// coordinates relation (x,y) or (y,x)
typedef enum _DIRECTION_WAY{
	Y_X,						  
	X_Y							
}DIRECTION_WAY; 

// Defines direction in which Ai would look and fire
// (-1, 0) - Left (1, 0) - Right
// (0, -1) - Up   (0, 1) - Down
typedef struct _AI_DIRECTION
{
	int dx; 
	int dy;
} AI_DIRECTION;



// AI resources
int ai_ship_count;						// Number of ship AI still has alive
int **ai_player_field;					// It is the field of AI where his ships are placed
int **ai_enemy_field;					// It is the field on whitch AI would mark his whots and enemy dead/hit ships
int **player_field;						// It is the client's field where his ships are placed, used to calculate hits and misses
COORDS ai_last_shot; 
COORDS ai_last_shot_suc;				// Coordinates of the last successful shot
AI_DIRECTION ai_direction; 
int got_target;							// Flag defining AI behavior: 0 - AI makes random shot; 1 - makes surround shot; 2 -  makes direct/revert shot
int *ships;								// Structure helping AI to watch over enemy ships and their condition



// Main functions that client 
// needs to invoke directly
message ai(message);											// Main function emulating conversation with another player
int ai_set_field(int **);										// AI needs to know about players ships so client must offer him a pointer to it through whis function

// Internal AI functions
void ai_init();													// Initialises all AI resources
void ai_uninit();												// Frees all allocated resources after the game is over
int ai_hit(int**, COORDS, int);									// Defines if the ship was hit and if it is dead now, also signals if the game is over and if client won or not
int ai_shoot(COORDS *coords);  
void ai_get_respond(enum _REQUESTS);							// defines AI reaction on events
void ai_clear_variants(int **);									// marks places where no more ships can be located
void ai_choose_direction(enum _REQUESTS); 
int ai_rand_cell(int **, COORDS *, DIRECTION_WAY const);		// Generates coordinates of random free cell on the field
int ai_rand_matr(int **);										// With it's help AI places his own ships
#endif 

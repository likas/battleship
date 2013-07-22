#include "ai.h"

void draw_cell(enum _CELL_STATE state)
{
	switch(state)
	{
		case CELL_NONE: printf("_"); break;
		case CELL_SHIP: printf("S"); break;
		case CELL_SHIP_FIRE: printf("@"); break;
		case CELL_MISS: printf("*"); break;
	}
}

void ai_draw(int **field_first, int **field_second)
{
	for(int i = 0; i < SIZE; i++)
    {
		for(int j = 0; j < SIZE; j++)
			draw_cell(field_first[i][j]);	
		printf("\t");	
		for(int j = 0; j < SIZE; j++)
			draw_cell(field_second[i][j]);	
		printf("\n");
	}	
}


int main()
{
rand();
rand();
rand();
/*	int test_area1[ SIZE ][ SIZE ] = { {1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
									  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
									  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
									  {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
									  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
									  {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
									  {0, 0, 1, 1, 1, 0, 0, 1, 0, 0},
									  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
									  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
									  {0, 0, 0, 0, 0, 1, 1, 1, 0, 0}
									};
*/
	player_field = (int **) malloc( sizeof(int*) * SIZE); 
    ai_enemy_field  = (int **) malloc (sizeof(int*) * SIZE);
	for(int i = 0; i < SIZE; i++)
	{
		player_field[i] = (int *)calloc( SIZE, sizeof(int) );
		ai_enemy_field[i]  = (int *)calloc( SIZE, sizeof(int) );
	}

	ai_init();
	// init_field
	ai_rand_matr( player_field );
	//ai_set_field( player_field );
	COORDS coords;
	do
	{
		ai_shoot( &coords );
		ai_get_respond(ai_hit(player_field, coords, AI));
		ai_clear_variants( ai_enemy_field );
		
		ai_draw( ai_enemy_field, player_field );
//	}while(getchar() != 'q');
	}while(1);
	ai_uninit();

	return 0;
}

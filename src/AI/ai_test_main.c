#include "ai.h"

void draw_cell(enum _CELL_STATE state)
{
	switch(state)
	{
		case CELL_NONE: printf("_"); break;
		case CELL_SHIP: printf("S"); break;
		case CELL_SHIP_FIRE: printf("@"); break;
		case CELL_MISS: printf("*"); break;
		default: break;
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
	printf("\n");	
}


int main()
{
	srand(time(NULL));
//	srand(234);	

	ai_init();
	ai_rand_matr( ai_player_field );
	long step = 0;
	do
	{
		COORDS coords = {-1, -1};
		ai_shoot( &coords );
		int ans = ai_hit(ai_player_field, coords, AI);
		if(ans == REQ_MISS) step++;
		if(ans == REQ_YOULOSE || ans == REQ_YOUWIN)
			break;
		ai_get_respond(ans);
     	ai_clear_variants( ai_enemy_field );
//		ai_draw( ai_enemy_field, ai_player_field );
//	}while(getchar() != 'q');
	}while(1);
	printf("%ld\n", step);
	ai_uninit();

	return 0;
}

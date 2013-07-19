#include "ai.h"

void draw_cell(enum _CELL_STATE state)
{
	switch(state)
	{
		case CELL_NONE: printf("O"); break;
		case CELL_SHIP: printf("S"); break;
		case CELL_SHIP_FIRE: printf("F"); break;
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
	int **fire_range = (int **) malloc( sizeof(int*) * SIZE); 
	int **test_area = (int **) malloc (sizeof(int*) * SIZE);
	for(int i = 0; i < SIZE; i++)
	{
		fire_range[i] = (int *)malloc( sizeof(int) * SIZE);
		test_area[i] = (int *)malloc( sizeof(int) * SIZE);
//		for(int j = 0; j < SIZE; j++)
//			fire_range[i][j] = test_area[i][j] = test_area1[i][j];
	}
	ai_rand_matr( test_area );
	COORDS coords;

	ai_init();
	// init_field
	ai_set_field( test_area );

	for ( int i = 0; i < SIZE; i++ ) {
		for ( int j = 0; j < SIZE; j++ ) {
			fire_range[ i ][ j ] = test_area[ i ][ j ];
		}
	}
	
	ai_draw( test_area, fire_range );
	do
	{
		ai_rand_cell( test_area, &coords );
		ai_shoot( &coords );
		ai_clear_variants( test_area );
		ai_draw( test_area, fire_range );
	}while(getchar() != 'q');

	ai_uninit();

	return 0;
}

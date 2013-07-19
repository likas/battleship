#include "ai.h"

int is_first = 0;
int first_start = 1;
void ai_draw(int **field_first, int **field_second)
{
	if(first_start)
		gui(), 
		De_Init(field_first, field_second), 
		first_start = 0;
	else
		render(field_first, field_second, is_first++),
		is_first%=2;
	getch();
}

int main()
{
	int test_area[ SIZE ][ SIZE ] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
									  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
									  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  
									  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
									  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
									  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
									  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
									  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
									  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	int fire_range[ SIZE ][ SIZE ] = { 0 };
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

	ai_rand_cell( test_area, &coords );
	ai_shoot( coords );
	ai_clear_variants( test_area );
	ai_draw( test_area, fire_range );

	ai_uninit();

	return 0;
}

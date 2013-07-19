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

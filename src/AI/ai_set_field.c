#include "ai.h"

int ai_set_field(int **field)
{
	if(!field)
		return 0;
	player_field = field;
	return 1;
}

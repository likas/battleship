#include "ai.h"

// TODO: add free statements here for all allocations in ai_init.c
void ai_uninit()
{
	free( ships );
}

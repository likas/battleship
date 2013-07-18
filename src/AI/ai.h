int ai_cells_left = 100; //Count unshoot cells
int **ai_field, **ai_player_field, **player_field;

typedef struct AI_DIRECTION
{
	int dx; 
	int dy;
}

typedef struct AI_COORDS
{
	int x;
	int y;
}

int ai_set_field(int **);
int ai_shoot(int x, int y);

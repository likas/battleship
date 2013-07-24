#include "client.h"
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


int with_ai(int is_manual)
{
	int turn=0;
	int g_o=0;
	COORDS hit_place;
	message ch_ai;
	ch_ai.command = MSG_SG;

	if(is_manual) {
		De_Init(SMAP,EMAP);	
		ras(SMAP);
	} else {
		ai_rand_matr(SMAP);
		De_Init(SMAP,EMAP);
	}	
	ai_set_field(SMAP);
	ch_ai=ai(ch_ai);
	if(ch_ai.params[0] == 'f')
	{
		turn=1;
	}
	while (g_o==0)
	{
	if (turn==1)
	{	
		do
		{
			hit_place = De_Move(EMAP);
			if ((hit_place.x==-1)&&(hit_place.y==-1))
			{
				ch_ai.command = REQ_DISCONNECT;
				ai(ch_ai);
				return REQ_DISCONNECT;
			}	
		} while (EMAP[hit_place.x][hit_place.y] != CELL_NONE);
//		printf("Enter coord:\n");
//		scanf("%d %d", &(hit_place.x), &(hit_place.y));
	ch_ai.command = MSG_AT;
		char buf[128];
		coords_atoi(buf,hit_place);
		//sscanf(ch_ai.params,"%s", buf);
		ch_ai.params[0]=buf[0];  
	        ch_ai.params[1]=buf[1];
		
		ch_ai=ai(ch_ai);
		switch (ch_ai.command) 
		{
			case REQ_MISS:
			{
				EMAP[hit_place.x][hit_place.y]=CELL_MISS;
				turn = 0;
				break;
			}
			case REQ_HIT:
			{
				EMAP[hit_place.x][hit_place.y]=CELL_SHIP_FIRE;
				break;
			}
			case REQ_YOUWIN:
			{
				EMAP[hit_place.x][hit_place.y]=CELL_SHIP_FIRE;
				round_ship(EMAP,hit_place.x,hit_place.y);	
				g_o=REQ_YOUWIN;
				break;
			}
			case REQ_DESTROYED:
			{
				EMAP[hit_place.x][hit_place.y]=CELL_SHIP_FIRE;
				round_ship(EMAP,hit_place.x,hit_place.y);	
//				render(SMAP,EMAP,1);
				break;
			}			
			
		}
//		FINchcell(hit_place.x,hit_place.y,EMAP[hit_place.x][hit_place.y],1);
		if (!g_o)
			guiturn(PLAYER,ch_ai.command);
	}
	else
	{
		
		ch_ai.command = MSG_HM;
		ch_ai=ai(ch_ai);		
		/*getting coordinates from params*/
		coords_itoa(ch_ai.params,&hit_place);
		switch (ch_ai.command)
		{
			case REQ_MISS:
			{
				SMAP[hit_place.x][hit_place.y]=CELL_MISS;
				turn = 1;
				break;
			}
			case REQ_HIT:
			{
				SMAP[hit_place.x][hit_place.y]=CELL_SHIP_FIRE;
				break;
			}
			case REQ_YOULOSE:
			{	
				SMAP[hit_place.x][hit_place.y]=CELL_SHIP_FIRE;
				g_o=REQ_YOULOSE;
				break;
			}
			case REQ_DESTROYED:
			{
				SMAP[hit_place.x][hit_place.y]=CELL_SHIP_FIRE;
				break;
			}
			
		}
//		FINchcell(hit_place.x,hit_place.y,SMAP[hit_place.x][hit_place.y],0);
		if (!g_o)
		{
			guiturn(ENEMY,ch_ai.command);
		}

	}
	render(SMAP, EMAP,1);
//	ai_draw(SMAP, EMAP);
	}	
	return g_o;
}

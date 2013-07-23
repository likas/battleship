#include "client.h"

int with_ai()
{
	int turn=0;
	int g_o=0;
	COORDS hit_place;
	message ch_ai;
	ch_ai.command = MSG_SG;
	ai_rand_matr(SMAP);
	/*creating field*/
	De_Init(SMAP,EMAP);
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
		hit_place = De_Move(EMAP);
		ch_ai.command = MSG_AT;
		char buf[128];
		coords_atoi(buf,hit_place);
		scanf(ch_ai.params,"%s", buf);
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
				g_o=1;
				break;
			}
			case REQ_DESTROYED:
			{
				EMAP[hit_place.x][hit_place.y]=CELL_SHIP_FIRE;
			}			
			
		}
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
				g_o=2;
				break;
			}
			case REQ_DESTROYED:
			{
				EMAP[hit_place.x][hit_place.y]=CELL_SHIP_FIRE;
			}
			
		}
	}
	render(SMAP, EMAP,1);
	}	
	return g_o;
}

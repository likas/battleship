#include "client.h"
#include "../mboi.h"
#include <stdlib.h>
#include <stdio.h>
/*-------------------------*/
void round_ship(int **smap,int x,int y)
{
    short int vis[SIZE][SIZE]={0};
    void r_ship(int x,int y)
    {
	if((vis[x][y])||(smap[x][y]==CELL_MISS))
	    return;
	vis[x][y]=1;
	if(smap[x][y]==CELL_NONE)
	{
	    smap[x][y]=CELL_MISS;
	    return;
	}
	if(smap[x][y]==CELL_SHIP_FIRE)
	    smap[x][y]==CELL_SHIP_DEAD;
	/*------------*/
	if((x-1>=0)&&(y-1>=0))
	    r_ship(x-1,y-1);
	if((x-1>=0)&&(y+1<SIZE))
	    r_ship(x-1,y+1);
	if((x+1<SIZE)&&(y-1>=0))
	    r_ship(x+1,y-1);
	if((x+1<SIZE)&&(y+1<SIZE))
	    r_ship(x+1,y+1);
	/*------------*/
	if(x-1>=0)
	    r_ship(x-1,y);
	if(x+1<SIZE)
	    r_ship(x+1,y);
	if(y-1>=0)
	    r_ship(x,y-1);
	if(y+1<SIZE)
	    r_ship(x,y+1);
	return;
    }
    r_ship(x,y);
}
/*-------------------------*/
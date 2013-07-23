#include "client.h"
#include "../mboi.h"
#include <stdlib.h>
#include <stdio.h>
//---------------------------
int gameover(int **smap)/*If game is over function (return 1) , if not (return 0)*/
{
    int i,j;
    for(i=0;i<SIZE;i++)
    for(j=0;j<SIZE;j++)
	if(smap[i][j]==CELL_SHIP)
	    return 0;
    return 1;
}
//---------------------------/*Example: int a[n][n]; typedef struct{int x; int y}shot; shot b;  shoot((int*)a,b);*/
int shoot(int **smap, COORDS a)/*0 - Miss ; 1 - Hit ship ; 2 - Ship killed ; -1 - ERROR*/
{
    short int vis[SIZE][SIZE]={0};
    short int i,j;
    int x=a.x;
    int y=a.y;
    /*-------------------*/
    if((x>=SIZE)||(y>=SIZE)||(x<0)||(y<0)||(smap[x][y]==CELL_MISS)||(smap[x][y]==CELL_SHIP_FIRE)||(smap[x][y]==CELL_SHIP_DEAD))
	return -1;
    /*-------------------*/
    int killed(int x,int y)/*Killed or not killed*/
    {
        vis[x][y]=1;
	if((smap[x][y]==CELL_NONE)||(smap[x][y]==CELL_MISS))
	    return 0;
	else if(smap[x][y]==CELL_SHIP)
	    return 1;
	else if(smap[x][y]==CELL_SHIP_FIRE)
	{
	    /*--------------------------*/
	    if(x-1>=0)
		if(!vis[x-1][y])
		    if(killed(x-1,y)==1)
			return 1;
	    /*--------------------------*/
	    if(x+1<SIZE)
		if(!vis[x+1][y])    
		    if(killed(x+1,y)==1)
			return 1;
	    /*--------------------------*/
	    if(y-1>=0)
		if(!vis[x][y-1])
		    if(killed(x,y-1)==1)
			return 1;
	    /*--------------------------*/
	    if(y+1<SIZE)
		if(!vis[x][y+1])
		    if(killed(x,y+1)==1)
			return 1;
	    /*--------------------------*/
	    return 0;
	}
    }
    /*-------------------*/
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
    /*-------------------*/
    if(smap[x][y]==CELL_NONE)/*If miss*/
    {	
	smap[x][y]=CELL_MISS;
	return REQ_MISS;
    }
    /*-------------------*/
    smap[x][y]=CELL_SHIP_FIRE;
    if(!killed(x,y))
    {
	for(i=0;i<SIZE;i++)
	    for(j=0;j<SIZE;j++)
		vis[i][j]=0;
	r_ship(x,y);
	return REQ_DESTROYED;/*If you kill the ship*/
    }
    else
	return REQ_HIT;/*If you just hit it*/
}
//-----------------------------------

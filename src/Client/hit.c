#include "client.h"
#include <stdlib.h>
#include <stdio.h>
//---------------------------
int gameover(int *smap)/*If game is over function (return 1) , if not (return 0) Ex: gameover((int*)a);*/
{
    int i;
    for(i=0;i<size*size;i++)
	if(*(smap+i)==1)
	    return 0;
    return 1;
}
//---------------------------/*Example: int a[n][n]; typedef struct{int x; int y}shot; shot b;  shoot((int*)a,b);*/
int shoot(int *smap, shot a)/*0 - Miss ; 1 - Hit ship ; 2 - Ship killed ; -1 - ERROR*/
{
    short int vis[size][size]={0};
    int x=a.x;
    int y=a.y;
    /*-------------------*/
    if((x>size)||(y>size)||(x<0)||(y<0))
	return -1;
    /*-------------------*/
    int killed(int x,int y)/*Killed or not killed*/
    {
        vis[x][y]=1;
	if((*(smap+x*size+y)==0)||(*(smap+x*size+y)==3))
	    return 0;
	else if(*(smap+x*size+y)==1)
	    return 1;
	else if(*(smap+x*size+y)==2)
	{
	    /*--------------------------*/
	    if(x-1>=0)
		if(!vis[x-1][y])
		    if(killed(x-1,y)==1)
			return 1;
	    /*--------------------------*/
	    if(x+1<size)
		if(!vis[x+1][y])    
		    if(killed(x+1,y)==1)
			return 1;
	    /*--------------------------*/
	    if(y-1>=0)
		if(!vis[x][y-1])
		    if(killed(x,y-1)==1)
			return 1;
	    /*--------------------------*/
	    if(y+1<size)
		if(!vis[x][y+1])
		    if(killed(x,y+1)==1)
			return 1;
	    /*--------------------------*/
	    return 0;
	}
    }
    /*-------------------*/
    if(!(*(smap+x*size+y)))/*If miss*/
    {	
	*(smap+x*size+y)=3;
	return 0;
    }
    /*-------------------*/
    *(smap+x*size+y)=2;
    if(!killed(x,y))
	return 2;/*If you kill the ship*/
    else
	return 1;/*If you just hit it*/
}
//-----------------------------------
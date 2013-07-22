#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "../mboi.h"
/*----------------------------*/
void ras(int *smap)
{
    int i,j,dir=0,x=0,y=0;// dir - направление в котором ставится корабль, x,y - координаты куда ставится корабль
    int key;
    int len=4;
    int f=0;
    int kor[4]={4,3,2,1};
    //---------------------
    while(1)
    {
	key=getch();
	switch(key)
	{
	    case KEY_UP:
		if(y>0)
		    y--;
		break;
	    case KEY_DOWN:
		if(!dir)
		{
		    if(y<size-1)
			y++;
		}
		else
		    if(y<size-len)
			y++;
		break;
	    case KEY_LEFT:
		if(x>0)
		    x--;
		break;
	    case KEY_RIGHT:
		if(dir)
		{
		    if(x<size-1)
			x++;
		}
		else
		    if(x<size-len)
		        x++;
		break;
	    case 10:
		if(!dir)
		{
		    f=0;
		    for(i=0;i<len;i++)
			if(*(smap+size*y+x+i))
			    f=1;
		    if(!f)
		    {
		        for(i=0;i<len;i++)
			    *(smap+size*y+x+i)=1;
			kor[len-1]--;
			if(!kor[len-1])
			    len--;
			if(!len)
			    return;
			
		    }
		}
		else
		{
		    f=0;
		    for(i=0;i<len;i++)
			if(*(smap+size*(y+i)+x))
			    f=1;
		    if(!f)
		    {
		        for(i=0;i<len;i++)
			    *(smap+size*(y+i)+x)=1;
			kor[len-1]--;
			if(!kor[len-1])
			    len--;
			if(!len)
			    return;
		    }
		}
		break;
	    case 32:
		if(dir)
		{
		    dir=0;
		    if(x+len>=size)
			x=size-len;
		}
		else
		{
		    dir=1;
		    if(y+len>=size)
			y=size-len;
		}
		break;
	}
    }
}
/*----------------------------*/

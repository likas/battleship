#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "../mboi.h"
#include "../GUI/gui.h"
/*----------------------------*/
void ras(int *smap)
{
    int i,j,dir=0,x=0,y=0;// dir - направление в котором ставится корабль, x,y - координаты куда ставится корабль
    int key;
    int len=4;
    int f=0;
    int kor[4]={4,3,2,1};
    //---------------------
    attron(A_REVERSE);
    FINchcell(x,y,2,0);
    attroff(A_REVERSE);
    while(1)
    {
	key=getch();
	
	FINchcell(x,y,2,0);
	switch(key)
	{
	    case 'w':
		if(y>0)
		    y--;
		break;
	    case 's':
		if(!dir)
		{
		    if(y<SIZE-1)
			y++;
		}
		else
		    if(y<SIZE-len)
			y++;
		break;
	    case 'a':
		if(x>0)
		    x--;
		break;
	    case 'd':
		if(dir)
		{
		    if(x<SIZE-1)
			x++;
		}
		else
		    if(x<SIZE-len)
		        x++;
		break;
	    case 10:
		if(!dir)
		{
		    f=0;
		    for(i=0;i<len;i++)
			if(*(smap+SIZE*y+x+i))
			    f=1;
		    if(!f)
		    {
		        for(i=0;i<len;i++)
			    *(smap+SIZE*y+x+i)=1;
			kor[len-1]--;
			if(!kor[len-1])
			    len--;
			if(!len)
			    return;
			render(&smap,0,0);
			attron(A_REVERSE);
			FINchcell(x,y,2,0);
			attroff(A_REVERSE);
		    }
		}
		else
		{
		    f=0;
		    for(i=0;i<len;i++)
			if(*(smap+SIZE*(y+i)+x))
			    f=1;
		    if(!f)
		    {
		        for(i=0;i<len;i++)
			    *(smap+SIZE*(y+i)+x)=1;
			kor[len-1]--;
			if(!kor[len-1])
			    len--;
			if(!len)
			    return;
			render(&smap,0,0);
			attron(A_REVERSE);
			FINchcell(x,y,2,0);
			attroff(A_REVERSE);
		    }
		}
		break;
	    case 32:
		if(dir)
		{
		    dir=0;
		    if(x+len>=SIZE)
			x=SIZE-len;
		}
		else
		{
		    dir=1;
		    if(y+len>=SIZE)
			y=SIZE-len;
		}
		break;
	}
    attron(A_REVERSE);
    FINchcell(x,y,2,0);
    attroff(A_REVERSE);
    }
}
/*----------------------------*/

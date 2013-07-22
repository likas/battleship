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
    int len=4;//длина текущего корабля
    int f=0;
    int kor[4]={4,3,2,1};//количество кораблей
    int b,e;
    //---------------------
    attron(A_REVERSE);
    FINchcell(x,y,2,0);//отрисовка выбора
    attroff(A_REVERSE);
    while(1)
    {
	key=getch();
	
	FINchcell(x,y,2,0);
	switch(key)//отслеживаем нажатие клавиш
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
	    case 10://если можно разместить корабль, размещаем (горизонтально)
		if(!dir)
		{
		    //------------------------
		    f=0; if(x>0) b=-1;	if(x<SIZE-1) e=1;
		    for(i=b;i<len+e;i++)
		    {
			if(*(smap+SIZE*y+x+i))
			    f=1;
			if(y>0)
			    if(*(smap+SIZE*(y-1)+x+i))
				f=1;
			if(y<SIZE-1)
			    if(*(smap+SIZE*(y+1)+x+i))
				f=1;
		    }
		    //------------------------
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
		else//вертикально
		{
		    f=0; if(y>0) b=-1; if(y<SIZE-1) e=1;
		    for(i=b;i<len+e;i++)//проверка на 
		    {
			if(*(smap+SIZE*(y+i)+x))
			    f=1;
			if(x>0)
			    if(*(smap+SIZE*(y+i)+x-1)) f=1;
			if(x<SIZE-1)
			    if(*(smap+SIZE*(y+i)+x+1)) f=1;
		    }
		    //----------------------------------
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
	    case 32://смена направления в котором будет осуществляться размещение
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

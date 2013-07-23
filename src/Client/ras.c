#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "../mboi.h"
#include "../GUI/gui.h"
/*----------------------------*/
void rend_ship(int x,int y,int dir,int len,int cl)//функция отрисовки корабля
{						//x,y координаты , dir направление, len длина
	int i;
	for(i=0;i<len;i++)//3 -water 4-ship
		if(!dir)
		{
		    if(!cl)
			FINchcell(x+i,y,4,0);
		    else
			FINchcell(x+i,y,3,0);
		}
		else
		{ 
		    if(!cl)
			FINchcell(x,y+i,4,0);
		    else
			FINchcell(x,y+i,4,0);
		}
}
/*----------------------------*/
void ras(int **smap)
{
    int i,j,dir=0,x=0,y=0;// dir - направление в котором ставится корабль, x,y - координаты куда ставится корабль
    int key;
    int len=4;//длина текущего корабля
    int f=0;
    int kor[4]={4,3,2,1};//количество кораблей
    int b,e;
    //---------------------
    
    rend_ship(x,y,dir,len,0);
    while(1)
    {
	key=getch();
	rend_ship(x,y,dir,len,1);
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
		    f=0;
		    b=0;
		    e=0; 
		    if(x>0) b=-1;
		    if(x<SIZE-len) e=1;
		    
		    for(i=b;i<len+e;i++)//проверяем присутстувие кораблей на соседних клетках, на 
		    {			//пересечение с другими кораблями
			if(/**(smap+SIZE*y+x+i)*/smap[y][x+i])
			    f=1;
			if(y>0)
			    if(/**(smap+SIZE*(y-1)+x+i)*/smap[y-1][x+i])
				f=1;
			if(y<SIZE-1)
			    if(/**(smap+SIZE*(y+1)+x+i)*/smap[y+1][x+i])
				f=1;
		    }
		    //------------------------
		    if(!f)//если помех нет, то размещаем корабль
		    {
		        for(i=0;i<len;i++)
			    /**(smap+SIZE*y+x+i)*/smap[y][x+i]=1;
			kor[len-1]--;
			if(!kor[len-1])
			    len--;
			if(!len)
			    return;
		    }
		}
		else//вертикальное раммещение
		{
		    f=0;
		    b=0;
		    e=0; 
		    if(y>0) b=-1;
		    if(y<SIZE-len) e=1;
		    
		    for(i=b;i<len+e;i++)
		    {
			if(/**(smap+SIZE*(y+i)+x)*/smap[y+i][x])
			    f=1;
			if(x>0)
			    if(/**(smap+SIZE*(y+i)+x-1)*/smap[y+i][x-1])
				f=1;
			if(x<SIZE-1)
			    if(/**(smap+SIZE*(y+i)+x+1)*/smap[y+i][x+1])
				f=1;
		    }
		    //----------------------------------
		    if(!f)
		    {
		        for(i=0;i<len;i++)
			    /**(smap+SIZE*(y+i)+x)*/smap[y+i][x]=CELL_SHIP;
			render(SMAP,EMAP,0);
			kor[len-1]--;
			if(!kor[len-1])
			    len--;
			if(!len)
			    return;
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
	rend_ship(x,y,dir,len,0);
    }
}
/*----------------------------*/

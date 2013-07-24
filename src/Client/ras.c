#include "client.h"
//#include "../mboi.h"
//#include "../GUI/gui.h"
/*----------------------------*/
void rend_ship(int x,int y,int dir,int len,int **temp,int **smap)//функция отрисовки корабля
{						//x,y координаты , dir направление, len длина
	int i,j;
	for(i=0;i<SIZE;i++)
	    for(j=0;j<SIZE;j++)
		temp[i][j]=CELL_NONE;

	for(i=0;i<len;i++)
		if(!dir)
		    temp[x+i][y]=CELL_SHIP_FIRE;
		else
		    temp[x][y+i]=CELL_SHIP_FIRE;
	
	for(i=0;i<SIZE;i++)
	    for(j=0;j<SIZE;j++)
		if(temp[i][j]==CELL_NONE)
		    temp[i][j]=smap[i][j];
	render(temp,smap,0);
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
    int **temp;
    temp=(int**)malloc(sizeof(int*)*SIZE);
    //---------------------
    for(i=0;i<SIZE;i++)
    {	
	temp[i]=(int*)malloc(sizeof(int)*SIZE);
	for(j=0;j<SIZE;j++)
	    smap[i][j]=CELL_NONE;
    }
    
    rend_ship(x,y,dir,len,temp,smap);
    while(1)
    {
	key=getchar();
	switch(key)//отслеживаем нажатие клавиш
	{
	    case 'w':
		if(x>0)
		{
		    x--;
		    rend_ship(x,y,dir,len,temp,smap);
		}
		break;
	    case 's':
		if(dir)
		{
		    if(x<SIZE-1)
		    {
			x++;
			rend_ship(x,y,dir,len,temp,smap);
		    }
		}
		else
		    if(x<SIZE-len)
		    {
			x++;
			rend_ship(x,y,dir,len,temp,smap);
		    }
		break;
	    case 'a':
		if(y>0)
		{
		    y--;
		    rend_ship(x,y,dir,len,temp,smap);
		}
		break;
	    case 'd':
		if(!dir)
		{
		    if(y<SIZE-1)
		    {
			y++;
			rend_ship(x,y,dir,len,temp,smap);
		    }
		}
		else
		    if(y<SIZE-len)
		    {
		        y++;
			rend_ship(x,y,dir,len,temp,smap);
		    }
		break;
	    case 'g'://если можно разместить корабль, размещаем (горизонтально)
		if(dir)
		{
		    //------------------------
		    f=0;
		    b=0;
		    e=0; 
		    if(y>0) b=-1;
		    if(y<SIZE-len) e=1;
		    
		    for(i=b;i<len+e;i++)//проверяем присутстувие кораблей на соседних клетках, на 
		    {			//пересечение с другими кораблями
			if(/**(smap+SIZE*y+x+i)*/smap[x][y+i]==CELL_SHIP)
			    f=1;
			if(x>0)
			    if(/**(smap+SIZE*(y-1)+x+i)*/smap[x-1][y+i]==CELL_SHIP)
				f=1;
			if(x<SIZE-1)
			    if(/**(smap+SIZE*(y+1)+x+i)*/smap[x+1][y+i]==CELL_SHIP)
				f=1;
		    }
		    //------------------------
		    if(!f)//если помех нет, то размещаем корабль
		    {
		        for(i=0;i<len;i++)
			    /**(smap+SIZE*y+x+i)*/smap[x][y+i]=CELL_SHIP;
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
		    if(x>0) b=-1;
		    if(x<SIZE-len) e=1;
		    
		    for(i=b;i<len+e;i++)
		    {
			if(/**(smap+SIZE*(y+i)+x)*/smap[x+i][y]==CELL_SHIP)
			    f=1;
			if(y>0)
			    if(/**(smap+SIZE*(y+i)+x-1)*/smap[x+i][y-1]==CELL_SHIP)
				f=1;
			if(y<SIZE-1)
			    if(/**(smap+SIZE*(y+i)+x+1)*/smap[x+i][y+1]==CELL_SHIP)
				f=1;
		    }
		    //----------------------------------
		    if(!f)
		    {
		        for(i=0;i<len;i++)
			    /**(smap+SIZE*(y+i)+x)*/smap[x+i][y]=CELL_SHIP;
			render(SMAP,EMAP,0);
			kor[len-1]--;
			if(!kor[len-1])
			    len--;
			if(!len)
			    return;
		    }
		}
		rend_ship(x,y,dir,len,temp,smap);
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
		rend_ship(x,y,dir,len,temp,smap);
		break;
	}
    }
}
/*----------------------------*/

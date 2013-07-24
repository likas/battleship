#include "gui.h"

void guiturn(int fl,int fl2)
{
	FINref(info,4,0);
	if(fl==PLAYER) 
		wprintw(info,"YOUR TURN");
	if(fl==ENEMY) 
		wprintw(info,"OPPONENT TURN"); 
	if(fl2==REQ_HIT) wprintw(info," :  HIT!");
	if(fl2==REQ_MISS) wprintw(info," :  MISS!");
        if(fl2==REQ_DESTROYED) wprintw(info," :  SHIP DESTROYED!");

	FINref(info,4,1); 


}



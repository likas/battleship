#include "gui.h"

void guiturn(int fl)
{
	FINref(info,4,0);
	if(fl==0) 
		wprintw(info,"YOUR TURN");
	else 
		wprintw(info,"OPPONENT TURN"); 
	FINref(info,4,1); 


}



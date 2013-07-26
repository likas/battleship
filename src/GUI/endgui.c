#include "gui.h"

void endgui(int fl)
{
	FINref(stdscr,1,0);
	switch(fl)
	{
		case REQ_YOULOSE: 
			ant_hello("GAME OVER! YOU LOSE!", "Press any key to escape");
			break;
		case REQ_YOUWIN:
			ant_hello("YOU WIN!","Press any key to escape");
			break;
		case REQ_DISCONNECT:
			ant_hello("YOU'VE LEFT BATTLEFIELD!!!","COWARD, press any key to escape");
			break;
		case REQ_NDISCONNECT:
			ant_hello("ENEMY'VE LEFT BATTLEFIELD!!!","COWARD, press any key to escape");
			break;
		default: ant_hello("GAME ACCIDENTALY FINISHED!","Press any key to escape"); break;
	}
	
	endwin();
}


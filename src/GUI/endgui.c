#include "gui.h"

void endgui(int fl)
{
getch();
FINref(stdscr,1,0);
if(fl==REQ_YOULOSE) ant_hello("GAME OVER! YOU LOSE!", "Press any key to escape");
else 
	if(fl==REQ_YOUWIN) ant_hello("YOU WIN!","Press any key to escape");
	else ant_hello("GAME ACCIDENTALY FINISHED!","Press any key to escape"); 
	
endwin();
}


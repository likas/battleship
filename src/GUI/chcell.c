#include "gui.h"



void FINchcell(int x, int y,int fl,int k)
{
WINDOW ***win;
	if(k==0) win=my_win;
		 else win=op_win;
FINref(win[x][y],fl,0);
}

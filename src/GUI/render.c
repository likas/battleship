#include "gui.h"


void render(int **my, int **op, int fl )
{
int i,j;
 for(i=0;i<10;i++)
    for(j=0;j<10;j++) {
	if(fl) FINref(op_win[i][j],op[i][j],0);
	FINref(my_win[i][j],my[i][j],0);
	}	
}

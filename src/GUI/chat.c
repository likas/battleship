#include "gui.h"


int FINchat(char* user, char* mess,int str)
{
WINDOW* win=chat;
int i,j;
chtype c;
	if(str==win->_maxy-1){
	
		for(i=1;i<win->_maxy ;i++)
	 	 for(j=1;j<win->_maxx;j++){
			c=mvwinch(win,i+1,j);
			mvwaddch(win,i,j,c);
		}	
	mvwprintw(win,str,1,"%s : %s",user,mess);
	FINref(win,2,1); 
	return str;
	}
else {
	mvwprintw(win,str+1,1,"%s : %s",user,mess);
	FINref(win,2,1);	
   }

return str+1;
}



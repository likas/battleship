#include "gui.h"

int De_Move(int **op_mas, COORDS* rt, char *str)
{        
	int key=0;
	char c;
	static int i=0,j=0;
	int strcount=0;
	flushinp();
	noecho();
	leaveok(op_win[i][j],TRUE);
	wbkgdset(op_win[i][j],COLOR_PAIR(op_mas[i][j])|A_REVERSE);
	wclear(op_win[i][j]);
	wborder(op_win[i][j],ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, '*', '*','*' ,'*');
	wmove(op_win[i][j],op_win[i][j]->_maxy/2,op_win[i][j]->_maxx/2-1);
	wprintw(op_win[i][j],"%c:%d",'a'+i,j);
	wrefresh(op_win[i][j]);
	do
	{
		keypad(op_win[i][j], TRUE);
		key=wgetch(op_win[i][j]);
		wbkgdset(op_win[i][j],COLOR_PAIR(op_mas[i][j]));
		wclear(op_win[i][j]);
		wborder(op_win[i][j],ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
//		wrefresh(op_win[i][j]);
	        wnoutrefresh(op_win[i][j]);
		switch(key)
		{
			//exit program
			case 'Q': case 27:
				return 0;
				break;
			case 'w': case KEY_UP:
				if(i!=0)
					i--;
				break;
			case 'a': case KEY_LEFT:
				if(j!=0)
					j--;
				break;
			case 'd': case KEY_RIGHT:
				if(j!=9)
					j++;
				break;
			case 's': case KEY_DOWN:
				if(i!=9)
					i++;
				break;
			case 'c':  
				keypad(chat,TRUE); 
				echo();
				wmove(chat,GUICHATLEN+1,1);
	/*			wclrtoeol(chat);
				FINref(chat,2,1);*/
				while(1)
				{
					c=wgetch(chat);
					if(c!=10) 
						str[strcount++]=c; 
					else {
						str[strcount]='\0';
						wmove(chat,GUICHATLEN+1,1);
		                                wclrtoeol(chat);
		                                FINref(chat,2,1);
						if(GUICHATLEN+1==chat->_maxy-1) {// wmove(chat,chat->_maxy,1);
										  wclrtoeol (chat);
										   FINref(chat,2,1); }
						break;	
					}
				}
				GUICHATLEN=FINchat(username,str,GUICHATLEN);
				noecho();
				strcount=0;
				return 2; 
				break;
		}
		wbkgdset(op_win[i][j],COLOR_PAIR(op_mas[i][j])|A_REVERSE);
	        wclear(op_win[i][j]);
		leaveok(op_win[i][j],TRUE);
	        wborder(op_win[i][j],ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, '*', '*', '*', '*'); 
		wmove(op_win[i][j],op_win[i][j]->_maxy/2,op_win[i][j]->_maxx/2-1);
		wprintw(op_win[i][j],"%c:%d",'a'+i,j);
		wnoutrefresh(op_win[i][j]);
		doupdate();
	}
	while(key!=10);
	rt->x = i;
	rt->y = j;
	return 1;
}

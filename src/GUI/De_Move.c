#include "gui.h"

COORDS De_Move(int **op_mas)
{        
	COORDS  rt;
	int key=0;
	char *str=malloc(255*sizeof(char));
	char c;
	static int i=0,j=0;
	int strcount=0;
	noecho();
	leaveok(op_win[i][j],TRUE);
	wbkgdset(op_win[i][j],COLOR_PAIR(op_mas[i][j])|A_REVERSE);
	wclear(op_win[i][j]);
	wborder(op_win[i][j],' ', ' ', ' ', ' ', '*', '*', '*', '*');
	wmove(op_win[i][j],op_win[i][j]->_maxy/2,op_win[i][j]->_maxx/2-1);
	wprintw(op_win[i][j],"%c:%d",'a'+i,j);
	wrefresh(op_win[i][j]);
	while(key!=10){
		key=wgetch(op_win[i][j]);
		wbkgdset(op_win[i][j],COLOR_PAIR(op_mas[i][j]));
		wclear(op_win[i][j]);
	//	wrefresh(op_win[i][j]);
	        wnoutrefresh(op_win[i][j]);
		switch(key){
			case 'q':
				endgui( -1 );
				rt.x = -1;
				rt.y = -1;
				return rt;
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
				while(1){
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
				break;
		}
		wbkgdset(op_win[i][j],COLOR_PAIR(op_mas[i][j])|A_REVERSE);
	        wclear(op_win[i][j]);
		leaveok(op_win[i][j],TRUE);
	        wborder(op_win[i][j],' ', ' ', ' ', ' ', '*', '*', '*', '*');
		wmove(op_win[i][j],op_win[i][j]->_maxy/2,op_win[i][j]->_maxx/2-1);
		wprintw(op_win[i][j],"%c:%d",'a'+i,j);
	       //wrefresh(op_win[i][j]);
		wnoutrefresh(op_win[i][j]);
		doupdate();
	}
	rt.x=i;
	rt.y=j;
	return rt;
}

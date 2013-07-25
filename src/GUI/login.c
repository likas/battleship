#include "gui.h"
int ant_login(int len) {

    WINDOW *win;
    int maxx, maxy, i, j, strx, stry;
    int w_maxy = 6;
    int w_maxx = 60;
    int x = 0;
    int y = 0;
    int symb = 0;
    char *str1 = "Enter your name:";
    char *str2 = "to continue press Enter";
    char *str3 = "to clear press key Delete";

   struct winsize wins;

   int term_height,term_width;
   ioctl(0, TIOCGWINSZ, &wins);
    
    HELLOFLAG=1;	
    FINref(stdscr,1,0);	
    maxy = wins.ws_row;
    maxx = wins.ws_col;
    win = newwin (w_maxy, w_maxx, (maxy - w_maxy) / 2, (maxx - w_maxx) / 2);
    FINref(win,2,0);	
    box (win, '*', '*');
    wbkgd (win, COLOR_PAIR(2) | A_BOLD);
    getyx (win, y, x);
    mvwaddstr (win, (w_maxy / 2) - 1, x+2, str1);
    getyx (win, y, x);
    stry = y;
    strx = x;
    mvwaddstr (win, y + 1, 2, str2);
    mvwaddstr (win, y + 2, 2, str3);
    
    i = 0;
    keypad(win,TRUE);
    FINref(win,2,1);	
	
    while ((symb != 10) && (i < len) ) {

	 wmove(stdscr, (maxy-w_maxy)/2+2 ,(maxx-w_maxx)/2+18);
        for(i=0; username[i]!='\0'; i++) addch(username[i]|COLOR_PAIR(2)); FINref(stdscr,2,1);
	
        symb = wgetch(stdscr);
        if(RFLAG) {RFLAG=0; delwin(win);  return 0; }
	
	ioctl(0,TIOCGWINSZ, &wins); 
	maxy = wins.ws_row;
    	maxx = wins.ws_col;

	if(symb==10 && strlen(username)==0){
		symb='\0';
		continue;
	}
        switch (symb) {
            case KEY_DC:
		wmove(stdscr, (maxy-w_maxy)/2+2 ,(maxx-w_maxx)/2+18);
                for (j=(maxx-w_maxx)/2+18; j<(maxx-w_maxx)/2+w_maxx-1; j++) addch(' ');
		FINref(stdscr,2,1);
                for (j = i; j >= 0; j--) {
                    username[j] = '\0';
                }
                i = 0;
                break;
            default:
                if ((symb >= 48 && symb <= 59) || (symb >= 65 && symb <= 90) || (symb >= 97 && symb <= 122)) {
                    username[i] = symb;
		    wmove(stdscr, (maxy-w_maxy)/2+2 ,(maxx-w_maxx)/2+18+i);
                    waddch (stdscr, username[i]);
                    FINref(stdscr,2,1);
                    i++;
                }
                break;
        }
    }

  FINref(stdscr,1,0); 		
  return 1;
}


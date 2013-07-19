#include "gui.h"
char* ant_login(int len) {

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
    FINref(stdscr,1,0);	
    maxy = stdscr->_maxy;
    maxx = stdscr->_maxx;
    win = newwin (w_maxy, w_maxx, (maxy - w_maxy) / 2, (maxx - w_maxx) / 2);
    box (win, '*', '*');
    wbkgd (win, COLOR_PAIR(2) | A_BOLD);
    getyx (win, y, x);
    mvwaddstr (win, (w_maxy / 2) - 1, x+2, str1);
    getyx (win, y, x);
    stry = y;
    strx = x;
    mvwaddstr (win, y + 1, 2, str2);
    mvwaddstr (win, y + 2, 2, str3);
    wmove (win, stry, strx);
    i = 0;
    keypad(win,TRUE);	
    while ((symb != 10) && (i < len) ) {
        symb = wgetch(win);
	if(symb==10 && strlen(username)==0){
		symb='\0';
		continue;
	}
        switch (symb) {
            case KEY_DC:
                wmove (win, stry, strx);
                wclrtoeol (win);
                for (j = i; j >= 0; j--) {
                    username[j] = '\0';
                }
                i = 0;
                break;
            default:
                if ((symb >= 48 && symb <= 59) || (symb >= 65 && symb <= 90) || (symb >= 97 && symb <= 122)) {
                    username[i] = symb;
                    waddch (win, username[i]);
                    wrefresh (win);
                    i++;
                }
                break;
        }
    }
keypad(stdscr,TRUE);
return username;
}


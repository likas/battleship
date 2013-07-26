#include "gui.h"

int ant_hello (char *str1, char *str2) {
	struct winsize wins;
  	ioctl(0, TIOCGWINSZ, &wins);

    WINDOW *win;
    int maxx, maxy;
    int w_maxy = 6;
    int w_maxx = 40;
    int x = 0;
    int y = 0;
    FINref(stdscr,1,0);
    maxy   = wins.ws_row;
    maxx   = wins.ws_col;
    win = newwin(w_maxy, w_maxx, (maxy - w_maxy) / 2, (maxx - w_maxx) / 2);
    box (win, '*', '*');
    wbkgd (win, COLOR_PAIR(2) | A_BOLD);
    mvwaddstr(win, (w_maxy/2) - 1, (w_maxx - strlen(str1)) / 2, str1);
    getyx (win, y, x);
    mvwaddstr (win, y + 1, (w_maxx - strlen(str2)) / 2, str2);
    wrefresh(win);

    if(RFLAG) {RFLAG=0; return 0;}	
    wgetch(win);
    if(RFLAG) {RFLAG=0; return 0;}	
    return 1;
}



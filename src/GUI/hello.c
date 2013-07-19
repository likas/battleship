#include "gui.h"

void ant_hello (char *str1, char *str2) {
    WINDOW *win;
    int maxx, maxy;
    int w_maxy = 6;
    int w_maxx = 40;
    int x = 0;
    int y = 0;
    FINref(stdscr,1,0);
    maxy   = stdscr->_maxy;
    maxx   = stdscr->_maxx;
    win = newwin(w_maxy, w_maxx, (maxy - w_maxy) / 2, (maxx - w_maxx) / 2);
    box (win, '*', '*');
    wbkgd (win, COLOR_PAIR(2) | A_BOLD);
    mvwaddstr(win, (w_maxy/2) - 1, (w_maxx - strlen(str1)) / 2, str1);
    getyx (win, y, x);
    mvwaddstr (win, y + 1, (w_maxx - strlen(str2)) / 2, str2);
    wrefresh(win);
    wgetch(win);
    return;
}



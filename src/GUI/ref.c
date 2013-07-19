#include "gui.h"

void FINref(WINDOW* win,int k, int fl)
{
wbkgdset(win,COLOR_PAIR(k));
//	wattrset(win, COLOR_PAIR(k));
if(!fl) wclear(win);
wrefresh(win);
//	wattrset(win, A_NORMAL);
}

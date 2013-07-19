#include "gui.h"

void Fscroll(WINDOW *win, int fl,int fl1)
{
char c;
int i;
if(!fl1)
{
for(i=1; i<win->_maxx-1;i++) {
        c=mvwinch(win,win->_cury,i);
        mvwaddch(win,win->_cury,i,c|A_NORMAL);
        }
}
wmove(win,win->_cury+fl,1);

for(i=1; i<win->_maxx-1;i++) {
        c=mvwinch(win,win->_cury,i);
        mvwaddch(win,win->_cury,i,c|A_REVERSE);
        }

wrefresh(win);
}


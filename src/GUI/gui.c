#include "gui.h"
int gui()
{

int term_height,term_width;
char c;
int i,j;

GUICHATLEN=0;
my_win=calloc(10,sizeof(WINDOW**));
op_win=calloc(10,sizeof(WINDOW**));
        for(i=0;i<10;i++){               
		my_win[i]=calloc(10,sizeof(WINDOW*));
		op_win[i]=calloc(10,sizeof(WINDOW*));
        }

initscr();
cbreak();
noecho();
clear();
//getch();


term_height=stdscr->_maxy;
term_width=stdscr->_maxx;


start_color();
init_pair(0,COLOR_BLACK,COLOR_WHITE);
init_pair(1,COLOR_WHITE,COLOR_BLACK);
init_pair(2,COLOR_GREEN,COLOR_BLUE); //water
init_pair(3,COLOR_BLACK,COLOR_WHITE);//ship
init_pair(4,COLOR_CYAN,COLOR_RED);//hit
init_pair(5,COLOR_YELLOW,COLOR_MAGENTA);//miss
init_pair(6,COLOR_BLACK,COLOR_CYAN);

keypad(stdscr,TRUE);
chat=newwin(term_height/4-2,term_width-2,term_height-term_height/4,1);


ant_hello("Welcome to SeaBattle","Press any key to continue");
ant_login(35);
FINref(stdscr,1,0);
FINref(chat,2,0);
GUICHATLEN=FINchat("SYSTEM","Hello",GUICHATLEN);
GUICHATLEN=FINchat(username,"Hi, System",GUICHATLEN);
return 0;
}

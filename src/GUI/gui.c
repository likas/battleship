#include "gui.h"

void sig(int handler)
{
int i,j,SIZEFLAG=0;
struct winsize wins;

int term_height,term_width;
ioctl(0, TIOCGWINSZ, &wins);

term_height=wins.ws_row;
term_width=wins.ws_col;
if(term_height <30 || term_width<50){
	endwin();
	SIZEFLAG=1;
//	system("clear");
	printf("\033[2J\n");
	printf("Minumum size is 50x30\n");
	return;
}
else SIZEFLAG=0;

if(!SIZEFLAG){
for(i=0;i<10;i++)
  for(j=0;j<10;j++)
	{
	delwin(my_win[i][j]);
	delwin(op_win[i][j]);	
        } 

delwin(chat);
delwin(info);


endwin();

GUICHATLEN=0;
initscr();
cbreak();
noecho();
keypad(stdscr, TRUE);

term_height=stdscr->_maxy;
term_width=stdscr->_maxx;


start_color();
init_pair(0,COLOR_BLACK,COLOR_WHITE);
init_pair(1,COLOR_WHITE,COLOR_BLACK);
init_pair(2,COLOR_GREEN,COLOR_BLUE); //water
init_pair(3,COLOR_BLACK,COLOR_WHITE);//ship
init_pair(4,COLOR_CYAN,COLOR_RED);//hit
init_pair(5,COLOR_MAGENTA,COLOR_YELLOW);//

//wsetattr(stdscr,COLOR_PAIR(0));
//FINref(stdscr,0,0);

keypad(stdscr,TRUE);
chat=newwin(term_height/4-2,term_width-1,term_height-term_height/4+2,1);

FINref(stdscr,1,0);
FINref(chat,2,0);
GUICHATLEN=FINchat("SYSTEM","Hello",GUICHATLEN);
GUICHATLEN=FINchat(username,"Hi, System",GUICHATLEN);

De_Init(MY,OP);
}

}


int gui()
{
signal(SIGWINCH,sig);

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
keypad(stdscr, TRUE);
clear();

term_height=stdscr->_maxy;
term_width=stdscr->_maxx;


start_color();
init_pair(0,COLOR_BLACK,COLOR_WHITE);
init_pair(1,COLOR_WHITE,COLOR_BLACK);
init_pair(2,COLOR_GREEN,COLOR_BLUE); //water
init_pair(3,COLOR_BLACK,COLOR_WHITE);//ship
init_pair(4,COLOR_CYAN,COLOR_RED);//hit
init_pair(5,COLOR_MAGENTA,COLOR_YELLOW);//miss
init_pair(6,COLOR_BLACK,COLOR_CYAN);

keypad(stdscr,TRUE);
chat=newwin(term_height/4-2,term_width-2,term_height-term_height/4+2,1);


ant_hello("Welcome to SeaBattle","Press any key to continue");
ant_login(35);
FINref(stdscr,1,0);
FINref(chat,2,0);
GUICHATLEN=FINchat("SYSTEM","Hello",GUICHATLEN);
GUICHATLEN=FINchat(username,"Hi, System",GUICHATLEN);
return 0;
}

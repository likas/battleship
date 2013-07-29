#include "gui.h"


void sig(int handler)
{
	int i,j,SIZEFLAG=0;
	struct winsize wins;
	RFLAG=1;
	int term_height,term_width;
	ioctl(0, TIOCGWINSZ, &wins);

	term_height=wins.ws_row;
	term_width=wins.ws_col;
		if(term_height <24 || term_width<50){
			endwin();
			SIZEFLAG=1;
			printf("\033[2J\n");
			printf("Minumum size is 50x24\n");
			return;
		}
		else
		  SIZEFLAG=0;
	
	if(!SIZEFLAG){
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
				
		if(HELLOFLAG==0) {
			FINref(stdscr,1,0); 
			if(ant_hello("Welcome to SeaBattle","Press any key to continue"))
				{HELLOFLAG=1; RFLAG=0;}
		}
		else if(LOGINFLAG==0) {
			FINref(stdscr,1,0);
		//	RFLAG=0; 
			if(ant_login())
				{LOGINFLAG=1; RFLAG=0;} 
	//		else RFLAG=1;
	 	}	
		
		else if(HELLOFLAG==1 && LOGINFLAG==1 && INITFLAG==1){
			chat=newwin(term_height/4-2,term_width-1,term_height-term_height/4+2,1);
			
			FINref(stdscr,1,0);
			FINref(chat,2,0);
			
			GUICHATLEN=FINchat("SYSTEM","Hello",GUICHATLEN);
			GUICHATLEN=FINchat(username,"Hi, System",GUICHATLEN);
		
			De_Init(MY,OP);
		}

	}

}


int gui()
{
signal(SIGWINCH,sig);

int term_height,term_width;
char c;
int i,j;

GUICHATLEN=0;
HELLOFLAG=0;
LOGINFLAG=0;
INITFLAG=0;
RFLAG=0;

struct winsize wins;

ioctl(0, TIOCGWINSZ, &wins);
if(wins.ws_row<24 || wins.ws_col<50){
	printf("\033[2J\n");
	printf("Minumum size is 50x24, reopen game with another sizes\n");
	exit(1);
}

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
HELLOFLAG=ant_hello("Welcome to SeaBattle","Press any key to continue");
LOGINFLAG=ant_login(35);

while((MODEFLAG = show_menu()) == BACK)
        if(MODEFLAG == QUIT) { endwin(); return; }


//FINref(stdscr,1,0);
return 0;
}

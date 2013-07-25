#include "gui.h"

WINDOW* win_bg_menu = NULL;
WINDOW* win_list_menu = NULL;
MENU* menu = NULL;
MENU* submenu = NULL;
ITEM* m_itms[ 4 ];
ITEM* subm_itms[ 4 ];
const int bg_menu_size_x = 20;
const int bg_menu_size_y = 7;
const int menu_size_x = 14;
const int menu_size_y = 3;  
const int bg_submenu_size_x = 27;
const int bg_submenu_size_y = 7;
const int submenu_size_x = 22;
const int submenu_size_y = 3;  

int show_menu();
int show_submenu();
int select_return( int );
void free_items( ITEM**, int );
void sig_handler( int );
void redraw_menu();
void redraw_submenu();
void init_m_itms();
void init_subm_itms();
extern sig( int handler );

int show_menu()
{
	struct sigaction new_action, old_action;
	new_action.sa_handler = sig_handler;
	sigemptyset( &new_action.sa_mask );
	new_action.sa_flags = 0;
	sigaction( SIGWINCH, NULL, &old_action );
	if ( old_action.sa_handler != SIG_IGN ) {
		sigaction( SIGWINCH, &new_action, NULL );
	}
	
	struct winsize window;
	ioctl(0, TIOCGWINSZ, &window);
	
	int term_win_sz_x = window.ws_col;
	int	term_win_sz_y = window.ws_row;
	int status = -1;
	
	init_m_itms();
	if ( win_bg_menu == NULL ) {
		delwin( win_bg_menu );
	}
	
	if ( win_list_menu == NULL ) {
		delwin( win_list_menu );
	}

	wbkgd( stdscr, COLOR_PAIR( 0 ) );
	refresh();	
	
	win_bg_menu = newwin( bg_menu_size_y, bg_menu_size_x, ( term_win_sz_y - bg_menu_size_y ) / 2 , \
					   ( term_win_sz_x - bg_menu_size_x ) / 2 );
	wbkgd( win_bg_menu, COLOR_PAIR( 2 ) );
	
	win_list_menu = newwin( menu_size_y, menu_size_x, ( term_win_sz_y - bg_menu_size_y ) / 2 + 3, \
					   ( term_win_sz_x - bg_menu_size_x ) / 2 + 3 );
	wbkgd( win_list_menu, COLOR_PAIR( 2 ) );

	menu = new_menu( m_itms );
	set_menu_format( menu, 3, 1 );
	set_menu_win( menu, win_list_menu );
	
	
	mvwprintw( win_bg_menu, 1, menu_size_x / 2 - 2, "MENU" );
	wrefresh( win_bg_menu );
	post_menu( menu );
	wrefresh( win_list_menu );
	
	while ( TRUE ) {
		switch ( getch() ) {
			case KEY_UP:
				menu_driver( menu, REQ_UP_ITEM );
				post_menu( menu );
				wrefresh( win_list_menu );
				break;
			case KEY_DOWN:
				menu_driver( menu, REQ_DOWN_ITEM );
				post_menu( menu );
				wrefresh( win_list_menu );
				break;
			case 10:
				status = select_return( item_index( current_item( menu ) ) ); 
				unpost_menu( menu );
				free_items( m_itms, 3 );
				free_menu( menu );
				menu = NULL;	
				delwin( win_list_menu );
				win_list_menu = NULL;
				delwin( win_bg_menu );
				win_bg_menu = NULL;
				refresh();
				sigaction( SIGWINCH, &old_action, NULL );
				return status;	
				break;
			default:
				break;
		}
	}
}

void init_m_itms()
{
	char* menu_choices[] = { "SINGLE PLAYER",
							 "MULTIPLAYER",
							 "QUIT" };

	m_itms[ 0 ] = new_item( menu_choices[0], "" );
	m_itms[ 1 ] = new_item( menu_choices[1], "" );
	m_itms[ 2 ] = new_item( menu_choices[2], "" );
	m_itms[ 3 ] = NULL;
}

void init_subm_itms() 
{
	char* submenu_choices[] = { "PLACE SHIPS YOURSELF",
								"PLACE SHIPS RANDOMLY",
								"BACK" };

	subm_itms[ 0 ] = new_item( submenu_choices[0], "" );
	subm_itms[ 1 ] = new_item( submenu_choices[1], "" );
	subm_itms[ 2 ] = new_item( submenu_choices[2], "" );
	subm_itms[ 3 ] = NULL;
}

void sig_handler( int signal )
{
	if ( submenu != NULL ) {
		unpost_menu( submenu );
		redraw_submenu();
	} else if ( menu != NULL ) {
		unpost_menu( menu );
		redraw_menu();
	}
	//refresh();
	//wrefresh(win_bg_menu);
	//wrefresh(win_list_menu);
}

void redraw_menu()
{
	clear();
	refresh();
	struct winsize window;
	ioctl(0, TIOCGWINSZ, &window);
	
	int term_win_sz_x = window.ws_col;
	int term_win_sz_y = window.ws_row;
	free_items( m_itms, 3 );
	free_menu( menu );
	if ( win_bg_menu != NULL ) {
		delwin( win_bg_menu );
	}
	
	if ( win_list_menu != NULL ) {
		delwin( win_list_menu );
	}
	refresh();
	init_m_itms();
	win_bg_menu = newwin( bg_menu_size_y, bg_menu_size_x, ( term_win_sz_y - bg_menu_size_y ) / 2 , \
						( term_win_sz_x - bg_menu_size_x ) / 2 );
	wbkgd( win_bg_menu, COLOR_PAIR( 2 ) );
	
	win_list_menu = newwin( menu_size_y, menu_size_x, ( term_win_sz_y - bg_menu_size_y ) / 2 + 3, \
					      ( term_win_sz_x - bg_menu_size_x ) / 2 + 3 );
	wbkgd( win_list_menu, COLOR_PAIR( 2 ) );
	menu = new_menu( m_itms );
	set_menu_format( menu, 3, 1 );
	set_menu_win( menu, win_list_menu );
	refresh();
	mvwprintw( win_bg_menu, 1, bg_menu_size_x / 2 - 2, "MENU" );
	wrefresh( win_bg_menu );
	post_menu( menu );
	wrefresh( win_list_menu );
	refresh();
}

void redraw_submenu()
{
	clear();
	refresh();
	struct winsize window;
	ioctl(0, TIOCGWINSZ, &window);
	
	int term_win_sz_x = window.ws_col;
	int	term_win_sz_y = window.ws_row;
	free_items( subm_itms, 3 );
	free_menu( submenu );
	if ( win_bg_menu != NULL ) {
		delwin( win_bg_menu );
	}
		
	if ( win_list_menu != NULL ) {
		delwin( win_list_menu );
	}
	init_subm_itms();
	win_bg_menu = newwin( bg_submenu_size_y, bg_submenu_size_x, ( term_win_sz_y - bg_submenu_size_y ) / 2 , \
						( term_win_sz_x - bg_submenu_size_x ) / 2 );
	wbkgd( win_bg_menu, COLOR_PAIR( 2 ) );
	
	win_list_menu = newwin( submenu_size_y, submenu_size_x, ( term_win_sz_y - bg_submenu_size_y ) / 2 + 3, \
	 				      ( term_win_sz_x - bg_submenu_size_x ) / 2 + 3 );
	wbkgd( win_list_menu, COLOR_PAIR( 2 ) );
	submenu = new_menu( subm_itms );
	set_menu_format( submenu, 3, 1 );
	set_menu_win( submenu, win_list_menu );
	refresh();
	mvwprintw( win_bg_menu, 1, bg_submenu_size_x / 2 - 2, "MENU" );
	wrefresh( win_bg_menu );
	post_menu( submenu );
	wrefresh( win_list_menu );
	refresh();
}

int select_return( int item_indx )
{
	int stat;
	switch( item_indx ) {
		case 0:
			stat = show_submenu();
			if ( stat != BACK ) {
				return ( 2 | stat );
			} else {
			   return BACK;	
			}
			break;
		case 1:
			return show_submenu();
			break;
		case 2:
			return QUIT;
			break;
		case 3:
			return 1;
			break;
		case 4:
			return 0;
			break;
		case 5:
			return BACK;
			break;
		default:
			return -1;
			break;
	}
}

int show_submenu()
{
	struct winsize window;
	ioctl(0, TIOCGWINSZ, &window);
	
	int term_win_sz_x = window.ws_col;
	int	term_win_sz_y = window.ws_row;
	int status = -1;

	
	init_subm_itms();
	if ( win_bg_menu == NULL ) {
		delwin( win_bg_menu );
	}
	
	if ( win_list_menu == NULL ) {
		delwin( win_list_menu );
	}

	wbkgd( stdscr, COLOR_PAIR( 0 ) );
	refresh();

	win_bg_menu = newwin( bg_submenu_size_y, bg_submenu_size_x, ( term_win_sz_y - bg_submenu_size_y ) / 2 , \
					   ( term_win_sz_x - bg_submenu_size_x ) / 2 );
	wbkgd( win_bg_menu, COLOR_PAIR( 2 ) );
	
	win_list_menu = newwin( submenu_size_y, submenu_size_x, ( term_win_sz_y - bg_submenu_size_y ) / 2 + 3 , \
					   ( term_win_sz_x - bg_submenu_size_x ) / 2 + 3 );
	wbkgd( win_list_menu, COLOR_PAIR( 2 ) );

	submenu = new_menu( subm_itms );
	set_menu_format( submenu, 3, 1 );
	set_menu_win( submenu, win_list_menu );
	
	mvwprintw( win_bg_menu, 1, menu_size_x / 2 - 2, "MENU" );
	wrefresh( win_bg_menu );
	post_menu( submenu );
	wrefresh( win_list_menu );
	
	while ( TRUE ) {
		switch ( getch() ) {
			case KEY_UP:
				menu_driver( submenu, REQ_UP_ITEM );
				post_menu( submenu );
				wrefresh( win_list_menu );
				break;
			case KEY_DOWN:
				menu_driver( submenu, REQ_DOWN_ITEM );
				post_menu( submenu );
				wrefresh( win_list_menu );
				break;
			case 10:
				status = select_return( ( item_index( current_item( submenu ) ) + 3 ) ); 
				unpost_menu( submenu );
				free_items( subm_itms, 3 );
				free_menu( submenu );
				submenu = NULL;	
				delwin( win_list_menu );
				win_list_menu = NULL;
				delwin( win_bg_menu );
				win_bg_menu = NULL;
				refresh();
				redraw_menu();
				refresh();
				return status;
				break;
			default:
				break;
		}
	}
}

void free_items( ITEM** items, int n_items )
{ int i;
	for (i = 0; i < n_items; i++) {
		free_item( items[ i ] );
	}
}

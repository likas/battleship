#include "gui.h"
int show_menu();
int show_submenu();
int select_return( int );

int show_menu()
{
	WINDOW* win_menu;
	WINDOW* win_submenu;
	MENU* menu;
	ITEM* menu_items[ 4 ];
	int menu_size_x = 20;
	int menu_size_y = 7;
	int submenu_size_x = 14;
	int submenu_size_y = 3;  
	int term_win_sz_x = stdscr->_maxx;
	int	term_win_sz_y = stdscr->_maxy;
	
	char* menu_choices[] = { "SINGLE PLAYER",
							 "MULTIPLAYER",
							 "QUIT" };

	init_pair( 0, COLOR_WHITE, COLOR_BLACK );
	init_pair( 1, COLOR_RED, COLOR_BLUE );
	wbkgd( stdscr, COLOR_PAIR( 0 ) );
	win_menu = newwin( menu_size_y, menu_size_x, term_win_sz_y / 2 + 4, \
					   ( term_win_sz_x - menu_size_x ) / 2 );
	wbkgd( win_menu, COLOR_PAIR( 1 ) );
	
	win_submenu = newwin( submenu_size_y, submenu_size_x, term_win_sz_y / 2 + 7, \
					   ( term_win_sz_x - menu_size_x ) / 2 + 3 );
	wbkgd( win_submenu, COLOR_PAIR( 1 ) );

	menu_items[ 0 ] = new_item( menu_choices[0], "" );
	menu_items[ 1 ] = new_item( menu_choices[1], "" );
	menu_items[ 2 ] = new_item( menu_choices[2], "" );
	menu_items[ 3 ] = NULL;
	menu = new_menu( menu_items );
	set_menu_format( menu, 3, 1 );
	set_menu_win( menu, win_submenu );
	
	refresh();
	
	mvwprintw( win_menu, 1, menu_size_x / 2 - 2, "MENU" );
	wrefresh( win_menu );
	post_menu( menu );
	wrefresh( win_submenu );
	
	while ( TRUE ) {
		switch ( getch() ) {
			case KEY_UP:
				menu_driver( menu, REQ_UP_ITEM );
				post_menu( menu );
				wrefresh( win_submenu );
				break;
			case KEY_DOWN:
				menu_driver( menu, REQ_DOWN_ITEM );
				post_menu( menu );
				wrefresh( win_submenu );
				break;
			case 10:
				return select_return( item_index( current_item( menu ) ) ); 
				break;
			default:
				break;
		}
	}
}

int select_return( int item_indx )
{
	switch( item_indx ) {
		case 0:
			return show_submenu();
			break;
		case 1:
			return MULTI;
			break;
		case 2:
			return QUIT;
			break;
		case 3:
			return SINGLE;
			break;
		case 4:
			return SINGLE_R;
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
	WINDOW* win_menu;
	WINDOW* win_submenu;
	MENU* submenu;
	ITEM* submenu_items[ 4 ];
	int menu_size_x = 26;
	int menu_size_y = 7;
	int submenu_size_x = 22;
	int submenu_size_y = 3;  
	int term_win_sz_x = stdscr->_maxx;
	int	term_win_sz_y = stdscr->_maxy;
	
	char* menu_choices[] = { "PLACE SHIPS YOURSELF",
							 "PLACE SHIPS RANDOMLY",
							 "BACK" };

	init_pair( 0, COLOR_WHITE, COLOR_BLACK );
	init_pair( 1, COLOR_RED, COLOR_BLUE );
	wbkgd( stdscr, COLOR_PAIR( 0 ) );
	win_menu = newwin( menu_size_y, menu_size_x, term_win_sz_y / 2 + 4, \
					   ( term_win_sz_x - menu_size_x ) / 2 );
	wbkgd( win_menu, COLOR_PAIR( 1 ) );
	
	win_submenu = newwin( submenu_size_y, submenu_size_x, term_win_sz_y / 2 + 7, \
					   ( term_win_sz_x - menu_size_x ) / 2 + 3 );
	wbkgd( win_submenu, COLOR_PAIR( 1 ) );

	submenu_items[ 0 ] = new_item( menu_choices[0], "" );
	submenu_items[ 1 ] = new_item( menu_choices[1], "" );
	submenu_items[ 2 ] = new_item( menu_choices[2], "" );
	submenu_items[ 3 ] = NULL;
	submenu = new_menu( submenu_items );
	set_menu_format( submenu, 3, 1 );
	set_menu_win( submenu, win_submenu );
	
	refresh();
	
	mvwprintw( win_menu, 1, menu_size_x / 2 - 2, "MENU" );
	wrefresh( win_menu );
	post_menu( submenu );
	wrefresh( win_submenu );
	
	while ( TRUE ) {
		switch ( getch() ) {
			case KEY_UP:
				menu_driver( submenu, REQ_UP_ITEM );
				post_menu( submenu );
				wrefresh( win_submenu );
				break;
			case KEY_DOWN:
				menu_driver( submenu, REQ_DOWN_ITEM );
				post_menu( submenu );
				wrefresh( win_submenu );
				break;
			case 10:
				return select_return( ( item_index( current_item( submenu ) ) + 3 ) ); 
				break;
			default:
				break;
		}
	}
}

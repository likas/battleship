#include "gui.h"

int ant_player_list (message *list, int leng) {

    int indent = 1;
    int maxy, maxx, lmaxy, lmaxx, rmaxy, rmaxx, rcurx, lcury, lcurx, i, key;
    WINDOW *left, *right;
    maxy  = stdscr->_maxy;
    maxx  = stdscr->_maxx;
    int start=0;
    char c;
    int ret;	
   
   FINref(chat,2,1);	
    //left window
    lmaxy = (3 * maxy) / 4;
    lmaxy = lmaxy - (2 * indent);
    lmaxx = (3 * maxx) / 4;
    lmaxx = lmaxx - (2 * indent);
    left  = newwin (lmaxy, lmaxx, indent, indent);
    wbkgd (left, COLOR_PAIR(2) | A_BOLD);
        wclear(left);
    box (left, '*', '*');

    //right window
    rmaxy = lmaxy;
    rmaxx = maxx - lmaxx;
    rmaxx = rmaxx - (3 * indent);
    rcurx = 2 * indent;
    rcurx = rcurx + lmaxx;
    right = newwin (rmaxy, rmaxx, indent, rcurx);
    wbkgd (right, COLOR_PAIR(2) | A_BOLD);
    wclear(right);
    box (right, '*', '*');
    lcury = 1;    lcurx = 2;
    wmove (left, lcury, lcurx);
    for (i = 0; i < leng && i<left->_maxy-1; i++) {
        waddstr (left, list[i].params);
        lcury++;
        lcurx = indent + 1;
        wmove (left, lcury, lcurx);
    };
    wrefresh(right);	

    lcury = indent + 1;
        wmove(left,1,2);
        Fscroll(left,0,1);
        wrefresh(left);
    key = 0;
	keypad(left,TRUE);
    while (1) {
        key = wgetch(left);
        switch (key) {
            case 's': case KEY_DOWN:
		if(left->_cury==leng) break;
                if(left->_cury==left->_maxy-1 && start+left->_maxy<=leng){
                        start++;
                        wclear(left);
                        box (left, '*', '*');
                        wmove(left,1,2);
                        wrefresh(left);
                        lcury=1;
                        for(i=start; i<start+left->_maxy-1; i++){
                        wprintw(left,"%s",list[i].params);
                         if(i!=start+left->_maxy-2) wmove(left,lcury+1,2);
                        lcury++;
                        if(i==leng) break;
                        }
                Fscroll(left,0,1);
                }
                else
                        if(left->_cury<left->_maxy-1)
                                Fscroll(left,1,0);
                break;

           case 'w': case KEY_UP:
                if(left->_cury==1 && start!=0){
                        start--;
                        wclear(left);
                        box (left, '*', '*');
                        wmove(left,1,2);
                        wrefresh(left);
                        lcury=1;
                        for(i=start; i<start+left->_maxy-1; i++){
                        wprintw(left,"%s",list[i].params);
                         if(i!=start+left->_maxy-2) wmove(left,lcury+1,2);
                        lcury++;
                        if(i==leng) break;
                        }
                        wmove(left,1,2);
                        Fscroll(left,0,1);
                }
                else
                        if(left->_cury>1)
                                Fscroll(left,-1,0);

                break;
	    case 'r': case 'R': return -1; break;	
	    case 10:
		 for(i=0;i<100;i++) opname[i]='\0';
		  ret=left->_cury-1+start;
		 for(i=2;c!=' ' &&  c!='\n'; i++){
		  c=mvwinch(left,left->_cury,i);
		  opname[i-2]=c;
		  }
		 opname[i-2]='\0';
		 mvwprintw(right,2,2,"You opponent: %s NUM=%d",opname,ret);
		 FINref(right,2,1);
	         wgetch(right);
		
		FINref(stdscr,1,0);
		 return ret ;	
		 break; 	
            default:
                break;
        }
    }

  }





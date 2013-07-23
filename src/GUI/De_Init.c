#include "gui.h"
int HLEFT=1;
int HRIGHT=1;
int HMID=3;

int De_Init(int **my_mas, int **op_mas){
/*******************************************************************************
	*i,j счетчики для перехода и прорисовки отдельных окон
	*префикс my_ используется для параметров окна игрока
	*префикс op_ - для параметров окна оппонента
		-stpoint - точка левого верхнего угла, от которого происходит 
		прорисовка окна ([0] - y, [1] - x)
		-{xmax,ymxa} максимальные координаты инициализированного 
		основного окна
	*win[][] - окно, хранящее в себе состояние текущий ячейки поля
	*cell_ - префикс для характеристик ячейки
		-h - высота
		-w - ширина	
	*chat_ - префикс для характеристик чата
		-h - высота
		-w - ширина
*******************************************************************************/
	int i, j, xmax, ymax;
	int my_stpoint[2], op_stpoint[2];
	int cell_w,cell_h,chat_w,chat_h;

	my_stpoint[0]=1; my_stpoint[1]=1;
	xmax=stdscr->_maxx; ymax=stdscr->_maxy;
	chat_w=xmax; chat_h=5;
	cell_w=(xmax-HLEFT-HRIGHT-HMID)/(10*2); //2 поля по 10 ячеек
	op_stpoint[0]=1; op_stpoint[1]=xmax-HRIGHT-(cell_w*10);
	
	cell_h=(ymax-(ymax/4)-2)/(10);
	cell_h-1;

/*начальная отрисовка полей*/
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			my_win[i][j]=newwin(cell_h, cell_w, my_stpoint[0]+i*cell_h, my_stpoint[1]+j*cell_w);
			wbkgdset(my_win[i][j], COLOR_PAIR(my_mas[i][j]));
			wclear(my_win[i][j]);
	//		wrefresh(my_win[i][j]);
	wnoutrefresh(my_win[i][j]);		
			
			op_win[i][j]=newwin(cell_h, cell_w, op_stpoint[0]+i*cell_h,op_stpoint[1]+j*cell_w);
                        wbkgdset(op_win[i][j], COLOR_PAIR(op_mas[i][j]));
                        wclear(op_win[i][j]);
         //               wrefresh(op_win[i][j]);
	wnoutrefresh(op_win[i][j]);		
		}
	}
 info=newwin(2,20,my_stpoint[0]+10*cell_h+2, my_stpoint[1] );
 FINref(info,4,0);	  	
 doupdate();
	return 0;
}

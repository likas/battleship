#include "gui.h"

int main()
{  COORDS coord;
   int i,j;
    message *st=malloc(28 * sizeof(message));
  
    strcpy(st[0].params, "0 ");
    strcpy(st[1].params, "1 ");
    strcpy(st[2].params,"2 ");
    strcpy(st[3].params, "3 ");
    strcpy(st[4].params, "4 ");
    strcpy(st[5].params, "5 ");
    strcpy(st[6].params, "6 ");
    strcpy(st[7].params, "7 ");
    strcpy(st[8].params, "8 ");
    strcpy(st[9].params,"9 ");
    strcpy(st[10].params, "10 ");
    strcpy(st[11].params, "11 ");
    strcpy(st[12].params, "12 ");
    strcpy(st[13].params, "13 ");
    strcpy(st[14].params, "14 ");
    strcpy(st[15].params, "15 ");
    strcpy(st[16].params, "16 ");
    strcpy(st[17].params, "17 ");
    strcpy(st[18].params, "18 ");
    strcpy(st[19].params, "19 ");
    strcpy(st[20].params, "20 ");
    strcpy(st[21].params, "21 ");
    strcpy(st[22].params, "22 ");
    strcpy(st[23].params, "23 ");
    strcpy(st[24].params, "24 ");
    strcpy(st[25].params, "25 ");
    strcpy(st[26].params, "26 ");
    strcpy(st[27].params, "27 ");
    int leng = 28;


int **a=calloc(10,sizeof(int*));
int **b=calloc(10,sizeof(int*));
  for(i=0;i<10;i++){
                a[i]=(int *)calloc(10,sizeof(int));
                b[i]=(int *)calloc(10,sizeof(int));
		    for(j=0;j<10;j++) { a[i][j]=2; b[i][j]=2;}

    }


gui();
ant_player_list(st,leng);
De_Init(a,b);
guiturn(0);
//////////////////////////////////////////////////
coord=De_Move(b);
FINchcell(coord.x,coord.y,4,1);
//render(a,b,1);
guiturn(1);
endgui(1);
return 0;
}

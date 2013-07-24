#include "gui.h"

int main()
{  COORDS coord;
   int i,j;
    message *st=malloc(100 * sizeof(message));
  
    strcpy(st[0].params, "0 ");
    strcpy(st[1].params, "1 ");
    strcpy(st[2].params, "2 ");
    strcpy(st[3].params, "3 ");
    strcpy(st[4].params, "4 ");
    strcpy(st[5].params, "5 ");
    strcpy(st[6].params, "6 ");
    strcpy(st[7].params, "7 ");
    strcpy(st[8].params, "8 ");
    strcpy(st[9].params, "9 ");
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
    strcpy(st[28].params, "30 ");
    strcpy(st[29].params, "31 ");
    strcpy(st[30].params, "32 ");
    strcpy(st[31].params, "33 ");
    strcpy(st[32].params, "34 ");
    strcpy(st[33].params, "35 ");
    strcpy(st[34].params, "36 ");
    strcpy(st[35].params, "37 ");
    strcpy(st[36].params, "38 ");
    strcpy(st[37].params, "39 ");
    strcpy(st[38].params, "40 ");
    strcpy(st[39].params, "41 ");
    strcpy(st[40].params, "42 ");
    strcpy(st[41].params, "43 ");
    strcpy(st[42].params, "44 ");
    strcpy(st[43].params, "45 ");
    strcpy(st[44].params, "46 ");
    strcpy(st[45].params, "47 ");
    strcpy(st[46].params, "48 ");
    strcpy(st[47].params, "49 ");
    strcpy(st[48].params, "50 ");
    strcpy(st[49].params, "51");
    strcpy(st[50].params, "52");
    strcpy(st[51].params, "53 ");
    strcpy(st[52].params, "54 ");
    strcpy(st[53].params, "55 ");
    strcpy(st[54].params, "56 ");
    strcpy(st[55].params, "57 ");
    int leng = 56;


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
guiturn(PLAYER,REQ_HIT);
//////////////////////////////////////////////////
coord=De_Move(a);
if(coord.x==-1) { endgui(REQ_YOULOSE); return 0; }

FINchcell(coord.x,coord.y,4,1);
//render(a,b,1);
guiturn(ENEMY,REQ_MISS);
getch();
endgui(REQ_YOUWIN);
return 0;
}

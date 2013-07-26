#include"server.h"

#define size 10

int gameover(int **smap)/*If game is over function (return 1) , if not (return 0)*/
{
    int i,j;
    for(i=0;i<SIZE;i++)
    for(j=0;j<SIZE;j++)
    if(smap[i][j]==CELL_SHIP)
        return 0;
    return 1;
}
//---------------------------/*Example: int a[n][n]; typedef struct{int x; int y}shot; shot b;  shoot((int*)a,b);*/
int shoot(int **smap, COORDS a)/*0 - Miss ; 1 - Hit ship ; 2 - Ship killed ; -1 - ERROR*/
{
    short int vis[SIZE][SIZE]={0};
    short int i,j;
    int x=a.x;
    int y=a.y;
    /*-------------------*/
    if((x>=SIZE) || (y>=SIZE) || 
		(x<0)   || (y<0)    ||
        (smap[x][y]==CELL_MISS)||
        (smap[x][y]==CELL_SHIP_FIRE)||
        (smap[x][y]==CELL_SHIP_DEAD))
    	return -1;
    /*-------------------*/
    int killed(int x,int y)/*Killed or not killed*/
    {
        vis[x][y]=1;
    if((smap[x][y]==CELL_NONE)||(smap[x][y]==CELL_MISS))
        return 0;
    else if(smap[x][y]==CELL_SHIP)
        return 1;
    else if(smap[x][y]==CELL_SHIP_FIRE)
    {
        /*--------------------------*/
        if(x-1>=0)
        if(!vis[x-1][y])
            if(killed(x-1,y)==1)
            return 1;
        /*--------------------------*/
        if(x+1<SIZE)
        if(!vis[x+1][y])
            if(killed(x+1,y)==1)
            return 1;
        /*--------------------------*/
        if(y-1>=0)
        if(!vis[x][y-1])
            if(killed(x,y-1)==1)
            return 1;
        /*--------------------------*/
        if(y+1<SIZE)
        if(!vis[x][y+1])
            if(killed(x,y+1)==1)
            return 1;
        /*--------------------------*/
        return 0;
    }
    }
    /*-------------------*/
    void r_ship(int x,int y)
    {
    if((vis[x][y])||(smap[x][y]==CELL_MISS))
        return;
    vis[x][y]=1;
    if(smap[x][y]==CELL_NONE)
    {
        smap[x][y]=CELL_MISS;
        return;
    }
    if(smap[x][y]==CELL_SHIP_FIRE)
        smap[x][y]==CELL_SHIP_DEAD;
    /*------------*/
    if((x-1>=0)&&(y-1>=0))
        r_ship(x-1,y-1);
    if((x-1>=0)&&(y+1<SIZE))
        r_ship(x-1,y+1);
    if((x+1<SIZE)&&(y-1>=0))
        r_ship(x+1,y-1);
    if((x+1<SIZE)&&(y+1<SIZE))
        r_ship(x+1,y+1);
    /*------------*/
    if(x-1>=0)
        r_ship(x-1,y);
    if(x+1<SIZE)
        r_ship(x+1,y);
    if(y-1>=0)
        r_ship(x,y-1);
    if(y+1<SIZE)
        r_ship(x,y+1);
    return;
    }
    /*-------------------*/
    if(smap[x][y]==CELL_NONE)/*If miss*/
    {
    smap[x][y]=CELL_MISS;
    return REQ_MISS;
    }
    /*-------------------*/
    smap[x][y]=CELL_SHIP_FIRE;
    if(!killed(x,y))
    {
    for(i=0;i<SIZE;i++)
        for(j=0;j<SIZE;j++)
        vis[i][j]=0;
    r_ship(x,y);
    return REQ_DESTROYED;/*If you kill the ship*/
    }
    else
    return REQ_HIT;/*If you just hit it*/
}
//-----------------------------------



void *Game(args *arg){
    int ***field,ret,i,j,ready=0,shooter,receiver,x,y,tmp,id;
	struct pollfd fds[2];
    struct sockaddr_in servaddr;
    message mesg;
    COORDS XY;
    args temp;
    int proverka = -1;

    field = (int ***) malloc (2 * sizeof(int**));
    printf("id1: %d\n", arg->id1);
    printf("id2: %d\n", arg->id2);

    temp.id1 = arg->id1;
    temp.id2 = arg->id2;
    temp.thr_cnt = arg->thr_cnt;

    fds[0].fd = temp.id1;
    fds[0].events = POLLIN;
    fds[1].fd = temp.id2;
    fds[1].events = POLLIN;
    id = temp.thr_cnt;
    
    while (1) {
        ret = poll(fds, 2, 10000);
        printf("ret: %d\n", ret);
        if (ret == - 1)
            perror("Error poll");
        if (ret == 0)
            continue;
        for(i = 0; i < 2; i++){
            if(fds[i].revents & POLLIN){
                if( (ret=recv(fds[i].fd,(void *)&mesg,sizeof(message),0)) < 0){
                    perror("Error recv");
                    return;
                }
				printf("Cmd:%d Prm 0:%d\nPrm 1: %d\n", mesg.command, mesg.params[0], mesg.params[1]);
                if(ret==0){
                    close(fds[i].fd);
                    mesg.command=REQ_DISCONNECT;
                    for(j=0;j<2;j++)
                        if(j!=i)
                            if(send(fds[j].fd,(void *)&mesg,sizeof(message),0)<0){
                                perror("Error send");
                                return;
                            }
                    close(fds[j].fd);
                    thread_id[id]=0;
                    return;
                }
                switch(mesg.command){
                /*Receive player's game fields*/
                case MSG_SF:
					field[i] = (int **) malloc (sizeof(int *) * SIZE);
                    for(int u = 0; u < SIZE; u++)
					{
						field[i][u] = (int *) malloc (sizeof(int) * SIZE);
						if((ret=recv(fds[i].fd, field[i][u],(sizeof(int)*SIZE),0)) < 0)
						{
                        	perror("Error recv");
                        	return;
                    	}
					}
                    if(++ready==2){
							for(int j = 0; j < SIZE; j++)
							{
								for(int k = 0; k < SIZE; k++)
									printf("%d ", field[0][j][k]);
								printf("\t");
								for(int k = 0; k < SIZE; k++)
									printf("%d ", field[1][j][k]);
								printf("\n");
							}	
                        mesg.command=MSG_RQ;
                        srand(time(NULL));
                        if( (rand()%2)==0){
                            shooter=0;
                            receiver=1;
                            strcpy(mesg.params,"f");
                            if(send(fds[0].fd,(void *)&mesg,sizeof(message),0)<0){
                                perror("Error send");
                                return;
                            }
                            strcpy(mesg.params,"s");
                            if(send(fds[1].fd,(void *)&mesg,sizeof(message),0)<0){
                                perror("Error send");
                                return;
                            }
                        }else{
                            shooter=1;
                            receiver=0;
                            strcpy(mesg.params,"s");
                            if(send(fds[0].fd,(void *)&mesg,sizeof(message),0)<0){
                                perror("Error send");
                                return;
                            }
                            strcpy(mesg.params,"f");
                            if(send(fds[1].fd,(void *)&mesg,sizeof(message),0)<0){
                                perror("Error send");
                                return;
                            }
                        }
                    }
                    break;
                    /*Receive  message of chat*/
                case MSG_TT:
                    for(j=0;j<2;j++)
                        if(j!=i){
                            if(send(fds[j].fd,(void *)&mesg,sizeof(message),0)<0){
                                perror("Error send");
                                return;
                            }
                        }
                    break;
			/*Clinet disconnected*/
		case REQ_DISCONNECT:
			//close(fds[i].fd);
			for(j=0;j<2;j++)
                        if(j!=i){
                            if(send(fds[j].fd,(void *)&mesg,sizeof(message),0)<0){
                                perror("Error send disconnect");
                                exit(1);
                            }
                        }
		    break;
                    /*Receive attack data*/
                case MSG_AT:
                    if(i!=shooter) break;
					XY.x = (int)mesg.params[0];
					XY.y = (int)mesg.params[1];
					printf("Attack! %d %d\n", XY.x, XY.y);
					mesg.command=shoot(field[receiver], XY);
                    if(mesg.command==-1) break;	
                    if(mesg.command==REQ_MISS){
                        tmp=shooter;
                        shooter=receiver;
                        receiver=tmp;
                    }
                    for(j=0;j<2;j++)
                        if(send(fds[j].fd,(void *)&mesg,sizeof(message),0)<0){
                            perror("Error send");
                            return;
                        }
                    if((tmp=gameover(field[receiver]))==1){
                        //memset(mesg.params,0,128);
                        mesg.command=REQ_YOUWIN;
						printf("Game over");
                        if(send(fds[shooter].fd,(void *)&mesg,sizeof(message),0)<0){
                            perror("Error send");
                            return;
                        }
                        mesg.command=REQ_YOULOSE;
                        if(send(fds[receiver].fd,(void *)&mesg,sizeof(message),0)<0){
                            perror("Error send");
                            return;
                        }
						usleep(2000);
                        close(fds[0].fd);
                        close(fds[1].fd);
                        thread_id[id]=0;
                    	return;
					}
                    break;
					case MSG_RL:
					mesg.command = REQ_GAMESTARTED;
					if(send(fds[i].fd, (void *)&mesg, sizeof(message), 0) < 0){
						perror("Error answering to msg RL!");
						return;
					}
					break;	
                }
            }
        }
    }
}



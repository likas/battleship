#include "client.h"

int go_list()
{
	printf("go_list\n");
	message lists[16];
	int i=0;
	for(i=0; i<16; ++i){
		lists[i].command=-1;
		lists[i].params[0]=-1;
	}
	i=0;
	while ((i<16)){
		if(recv(GAME_TUNNEL,&lists[i],sizeof(message),0) <sizeof(message)){
			perror("error receiving list");
			exit(1);
		}
		if (lists[i].command == REQ_STORLIST){
			if(i==0){
				printf("stoplist acquired\n");
				return -1;
			}
			break;
		}
		if(lists[i].command == -1){
			/* i--; */
			continue;
		}
		i++;
	}
	printf("i=%d\n", i);
	if(lists[1].command==REQ_STORLIST){
		lists[0].command=-1;
		strcpy(lists[0].params, "No-one else in list. Press here or 'r' to refresh\n");
/*		printf("if called\n");  */
		/* ant_player_list(lists, 16);
		return lists[0i].command; */
		ant_player_list(lists,1);
		return -1;
	}else{
		int flag = ant_player_list(lists, i);
		if(flag == - 1) {
			return -1;
		}
		return lists[flag].command;
	
	}
	/* return lists[ant_player_list(lists,i)].command; */
}

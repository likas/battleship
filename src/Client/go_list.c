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
	if(i<0){
		printf("if called\n"); 
		/* ant_player_list(lists, 16);
		return lists[0].command; */
		return -1;
	}else{
		return lists[ant_player_list(lists,i)].command;
	}
	/* return lists[ant_player_list(lists,i)].command; */
}

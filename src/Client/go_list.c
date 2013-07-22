#include "client.h"

int go_list()
{
	message lists[16];
	int i=0;
	while ((i<16))
	{
		if(recv(TUNNEL,&lists[i],sizeof(message),0) <sizeof(message))
		{
			perror("error receiving list");
			exit(1);
		}
		if (lists[i].command == REQ_STORLIST)
		{
			if(i==0){
				return -1;
			}
			break;
		}
		if(lists[i].command == -1){
			i--;
			continue;
		}
		i++;
	}
	return lists[ant_player_list(lists,i)].command;
}

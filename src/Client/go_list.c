#include "client.h"

int go_list()
{
	message lists[16];
	int i=0;
	while ((i<16))
	{
		if(recv(TUNNEL,&lists[i],sizeof(message),0) <sizeof(message))
		{
			perror("error reciving list");
			exit(1);
		}
		if (lists[i].command == REQ_STORLIST)
		{
			break;
		}
		i++;
	}
	return lists[ant_player_list(lists,i)].command;
}

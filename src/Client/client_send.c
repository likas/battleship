#include "client.h"

int send_name(char* name)
{
	message	name_mes;
	name_mes.command= MSG_TSK.NN;
	sscanf(name,"%s",name_mes.params);
	if (send(ser_sock,name_mes,sizeof(name_mes),0)==sizeof(name_mes))
	{
		return 0;
	}
	return 1;
}

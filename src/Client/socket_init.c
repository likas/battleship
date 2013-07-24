/* #include "client.h" */
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../mboi.h"
extern int GAME_TUNNEL;
int socket_init(){
	/* int sock; */
/*	message received, sent; */
	struct sockaddr_in addr;
	GAME_TUNNEL=socket(AF_INET, SOCK_STREAM, 0);
	if(GAME_TUNNEL<0){
		perror("socket");
		exit(1);
	}
	addr.sin_family=AF_INET;
	addr.sin_port=htons(1999);
/*	inet_aton("127.0.0.1", &addr.sin_addr); */
/* 	inet_pton(AF_INET, "156.13.2.25", &addr.sin_addr); */
/* 	inet_pton(AF_INET, "192.168.3.1", &addr.sin_addr); */
 	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if(connect(GAME_TUNNEL, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		perror("connect");
		exit(1);
	}
/*	sent.command = 1024;
	sent.params[0]='c';
	send(GAME_TUNNEL, &sent, sizeof(message), 0);
	recv(GAME_TUNNEL, elset, sizeof(char)*4, 0); */
	
	return 1;
}

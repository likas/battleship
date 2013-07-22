/* #include "client.h" */
#include <netinet/in.h>
int socket_init(){
	int sock;
	struct sockaddr_in addr;
	sock=socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0){
		perror("socket");
		exit(1);
	}
	addr.sin_family=AF_INET;
	addr.sin_port=htons(3425);
	inet_pton(AF_INET, "192.168.3.1", &addr.sin_addr);
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		perror("connect");
		exit(1);
	}
	return sock;
}

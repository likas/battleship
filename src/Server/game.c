#include"server.h"



int game_sockd=-1;

void * Game(){
	int field[2][10][10],ret,i,ready=0,shooter,receiver;
	struct pollfd fds[2];
	struct sockaddr_in servaddr;
	message mesg;

	if( (game_sockd=socket(AF_INET,SOCK_STREAM,0)) <0 ){
		perror("Error socket");
		exit(1);
	}

	memset(&servaddr,0,sizeof(struct sockaddr_in));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(port);

	if(bind(game_sockd,(struct sockaddr *)&servaddr,sizeof(struct sockaddr))<0){
		perror("Error bind");
		exit(1);
	}

	listen(game_sockd,2);

	if( (fds[0].fd=accept(game_sockd,0,0)) <0){
		perror("Accept");
		exit(1);
	}
	fds[0].events=POLLIN;

	if( (fds[1].fd=accept(game_sockd,0,0)) <0){
		perror("Accept");
		exit(1);
	}
	fds[1].events=POLLIN;

	while(1){
		ret=poll(fds,2,10000);
		if(ret==-1)
			perror("Error poll");
		if(ret==0)
			continue;
		for(i=0;i<2;i++){
			if(fds[i].revents & POLLIN){
				if( (ret=recv(fds[i].fd,(void *)&mesg,sizeof(message))) < 0){
					perror("Error recv");
					exit(1);
				}
				switch(mesg.command){
					case HUINJ:
						if( (ret=recv(fds[i].fd,(void *)&field[i],sizeof(int)*100)) < 0){
							perror("Error recv");
							exit(1);
						}
						if(++ready==2){
							srand(time(NULL));
							if( (rand()%2)==0){
								shooter=0;
								receiver=1;
							}else{
								shooter=1;
								receiver=0;
							}
							
				}
			}
		}
	}
}

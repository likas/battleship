#include "socket/mboi/src/mboi.h"
#include "socket/h.h"
#include "./socket/mboi/src/Server/server.h"

#define MAX_PL 16
int thr_cnt = 0;
#define thr_max_cnt 50
pthread_t threads[thr_max_cnt];

typedef struct {
	int _id;
	char name[20];
}_game;

void thread() {
	if(game_sockd < 0) sleep(1);

	while(thread_id[thr_cnt] > 0 && thr_cnt < thr_max_cnt) 
		thr_cnt++;
	if(pthread_create(&threads[thr_cnt], NULL, &Game, &thr_cnt) < 0) {
		perror("create_tread");
		exit(1);
	}
}

void nn_sg(message* msg, Player* pl, _game** gm, int sock) {
	int ind = 0, i = 0;
	game_sockd = -1;
	switch(msg->command) {
		case MSG_NN:
			/*fill field name in struct Player*/
			while(msg->params[i] != '\0') {
				pl->name[i] = msg->params[i];
				i++;
			}
			/*fill struct game*/
			while(ind < MAX_PL && gm[ind]->_id > 0) ind++;
			
			gm[ind]->_id = pl->_id;
			while(pl->name[i] != '\0') {
				gm[ind]->name[i] = pl->name[i];
				i++;
			}
			/*Create structs for STARTLIST and STOPLIST*/
			message* start = (message*)malloc(sizeof(message));
			message* stop = (message*)malloc(sizeof(message));
			message* accept = (message*)malloc(sizeof(message));
			start->command = REQ_STARTLIST;
			stop->command = REQ_STORLIST;
			accept->command = REQ_ACCEPT;
			/*send to player rq ACCEPT*/
			send(sock, &accept, sizeof(accept), 0);
		
			/*send to player the list of gamers*/
			send(sock, &start, sizeof(start), 0);
			for(i = 0; i < MAX_PL; i++) {
				send(sock, &gm, sizeof(_game), 0);
			}
			send(sock, &stop, sizeof(stop), 0);

			free(start);
			free(stop);
			free(accept);
			break;
		case MSG_SG:
			thread();
			i = 0;
			int in = 0;
			int id  = atoi(msg->params);
			//printf("111\n");
			while(id != gm[in]->_id) in++;

			gm[in]->_id = -1;
			
			while(gm[in]->name[i] != '\0') {
				gm[in]->name[i] = ' ';
				i++;
			}
			
			i = 0;
			while(pl->name[i] != '\0') {
				pl->name[i] = ' ';
				i++;
			}
			pl->_id = -1;
			
			break;
		default:
			break;
	}

}


int main() { 
	int sock, sockfd, i = 0;
	struct sockaddr_in addr;
	_game** gm = (_game**)malloc(sizeof(_game*));
	*gm = (_game*)malloc(sizeof(_game));

	//message *msg = (message*)malloc(sizeof(message));
	Player* pl = (Player*)malloc(sizeof(Player));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("SOCKET");
		exit(1);
	}
	
	message* msg = (message*)malloc(sizeof(message));
	msg->command = MSG_SG;
	
	
	//	nn_sg((message *)buf, pl, gm, sockfd);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr *)&addr, \
		sizeof(struct sockaddr)) < 0) {
		perror("bind");
		exit(1);
	}

	if(listen(sockfd, 5) < 0) {
		perror("listen");
		close(sockfd);
		exit(1);
	}
	while(1)	
		nn_sg(msg, pl, gm, sockfd);
		//printf("client %d connected\n", inet_ntoa(addr.sin_addr));
	//while(1) {
		//printf("2\n");
		//sock = accept(sockfd, NULL, NULL);
		//if(sock < 0) {
		//	perror("sock");
		//	exit(1);
		//}
		//int child;
		//func();
		//if((child = fork()) == 0) {
			//close(sockfd);
			//printf("1\n");
			//recv(sock, &buf, sizeof(buf), 0);
			//printf("%d\n", ((message*)&buf)->command);
			//send(sock, &buf, sizeof(buf), 0);
		//	close(sock);
	//	}
	//}
	
	//pthread_exit(0);
	close(sockfd);
	//close(sock);
	free(msg);
	free(pl);
	free(gm);
	return 0;
}

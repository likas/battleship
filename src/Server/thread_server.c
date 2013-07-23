#include "../socket/mboi/src/mboi.h"
#include "../socket/h.h"
#include "../socket/mboi/src/Server/server.h"

#define MAX_PL 16
int thr_cnt = 0;
#define thr_max_cnt 50
pthread_t threads[thr_max_cnt];

typedef struct {
	int _id;
	char name[20];
}_game;

void* game(void* counter);
void thread();
//void nn_sg(message* msg, Player* pl, _game** gm, int sock);

int main() { 
	int sock, sockfd, i = 0;
	struct sockaddr_in addr;
	/*Create structs STARTLIST and STOPLIST*/
	message* req_start=(message*)malloc(sizeof(message));
	message* req_stop=(message*)malloc(sizeof(message));
	message* req_accept=(message*)malloc(sizeof(message));
	
	message* msg = (message*)malloc(sizeof(message));	
	message* buf = (message*)malloc(sizeof(message));
	
	Player** pl=(Player**)malloc(MAX_PL*sizeof(Player*));
	message** gm = malloc(MAX_PL * sizeof(message*));
	while(i < MAX_PL) {
		gm[i] = malloc(sizeof(message));
		pl[i] = malloc(sizeof(Player));
		i++;
	}
	req_start->command = REQ_STARTLIST;
	req_stop->command = REQ_STORLIST;
	req_accept->command = REQ_ACCEPT;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("SOCKET");
		exit(1);
	}
	
	for(i = 0; i < MAX_PL; i++) {
		gm[i]->command = -1;
		pl[i]->_id = -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(1);
	}

	int id = 0, i_pl = 0, ind = 0;
	listen(sockfd, MAX_PL);

	while(1) {
		if((sock = accept(sockfd, 0, 0)) < 0) {
			perror("sock");
			exit(1);
		}
	
		bzero(msg, sizeof(message));
		recv(sock, msg, sizeof(message), 0);//!!!!!!!!!!

		//`nn_sg(msg, pl[i_pl], gm, sock);
		//=============_nn_sg_=============
		game_sockd = -1;
		//printf("cmd = %d\n", msg->command);
		//switch(msg->command) {
		//	case MSG_NN:

		if(msg->command == MSG_NN) {
			for(i_pl = 0; pl[i_pl]->_id != -1; i_pl++);
			pl[i_pl]->_id = id;
			printf("\ni_pl = %d\n", i_pl);
			printf("id = %d\n", pl[i_pl]->_id);
		
				/*send to player rq ACCEPT*/
				sprintf(req_accept->params, "%d", pl[i_pl]->_id);
				send(sock,req_accept, sizeof(message),0);
				/*send to player the list of gamers*/
				send(sock, req_start, sizeof(message),0);
				for(i = 0; i < MAX_PL; i++) {
					//if(gm[i]->_id != -1)
					send(sock,gm[i],sizeof(message),0);
				}
				send(sock, req_stop, sizeof(message), 0);

				/*fill field name in struct Player*/
				for(i = 0; msg->params[i] != '\0'; i++)
					pl[i_pl]->name[i] = msg->params[i];
				//printf("name: %s\n", msg->params);

				/*fill struct game*/
				for(ind = 0; gm[ind]->command != -1 && \
					ind < MAX_PL;ind++);
				gm[ind]->command = pl[i_pl]->_id;
	
				for(i=0; pl[i_pl]->name[i] != '\0';i++)
					gm[ind]->params[i]=pl[i_pl]->name[i];
				//printf("gm_id=%d\n", gm[ind]->command);
		} 
		recv(sock, msg, sizeof(message), 0);
		if(msg->command == MSG_SG) {
			//for(i_pl = 0; pl[i_pl]->_id != -1; i_pl++);
			//pl[i_pl]->_id = id;
			//printf("\ni_pl = %d\n", i_pl);
			//printf("id = %d\n", pl[i_pl]->_id);
			//printf("Select_game\n");
				thread();
				i = 0;
				int in = 0;
				int id  = atoi(msg->params);
				//printf("id = %d\n", id);	
				//while(id != gm[in]->command) in++;
				for(in = 0; id != gm[in]->command &&\
					 gm[in]->command != -1; in++);

				gm[in]->command = -1;
				
				while(gm[in]->params[i] != '\0') {
					gm[in]->params[i] = ' ';
					i++;
				}
			
				i = 0;
				while(pl[i_pl]->name[i] != '\0') {
					pl[i_pl]->name[i] = ' ';
					i++;
				}
				pl[i_pl]->_id = -1;
			}

		id++;
			
		/*	close(sockfd);
			printf("bytes rec: %d\n", recv(sock, msg, sizeof(message), 0));
			printf("params: %s\n", msg->params);
		*/
	}
	close(sock);
	close(sockfd);
	
	free(buf);
	free(msg);
	
	free(req_start);
	free(req_stop);
	free(req_accept);
	
	free(pl);
	free(gm);
	return 0;
}

void* game(void* counter) {
	int i = 0;
	printf("\nCnt_thr = %d\n", (int)counter);
	for(i = 0; i < 10; i++) printf("%d ", i);
	printf("\n");
}

void thread() {
	if(game_sockd < 0) sleep(5);

	while(thread_id[thr_cnt] >= 0 && thr_cnt < thr_max_cnt) 
		thr_cnt++;
	if(pthread_create(&threads[thr_cnt], NULL, game, (void*)thr_cnt) < 0) {
		perror("error_create_thread");
		exit(1);
	}
}

//void nn_sg(message* msg, Player* pl, _game** gm, int sock) {}


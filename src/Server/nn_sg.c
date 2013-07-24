#include "server.h"

pthread_t threads[thr_max_cnt] = {-1};
//message** gm;

typedef struct {
	int id1;
	int id2;
	int thr_cnt;
} args;

void thread(args *game_arg) {
	int thr_cnt;
	
	for(thr_cnt = 0; thread_id[thr_cnt] > 0 && thr_cnt < thr_max_cnt; thr_cnt++);

	game_arg->thr_cnt = thr_cnt;
	if(pthread_create(&threads[thr_cnt], NULL, Game, (void*)&game_arg) < 0) {
		perror("error_create_thread");
		exit(1);
	}
}

void nn_sg(message* msg, Player** pl, int ind, struct pollfd **fd) {
	int id = 0, i_pl = 0, i = 0;

	message* req=(message*)malloc(sizeof(message));	
	args* game_args = (args*)malloc(sizeof(args));
	//gm = malloc(MAX_PL * sizeof(message*));

	/*while(i < MAX_PL) {
		gm[i] = malloc(sizeof(message));
		i++;
	}*/
	game_sockd = -1;
	if(msg->command == MSG_NN) {
			/*send to player rq ACCEPT*/
			//req->command = REQ_ACCEPT;
			//send(sock,req, sizeof(message),0);
			/*send to player the list of gamers*/
			req->command = REQ_STARTLIST;
			send(fd[ind]->fd, req, sizeof(message),0);
			for(i = 0; i < MAX_PL; i++) {
				send(fd[ind]->fd, pl[i], sizeof(message),0);
			}
			req->command = REQ_STORLIST;
			send(fd[ind]->fd, req, sizeof(message), 0);

				/*fill field name in struct Player*/
			for(i = 0; msg->params[i] != '\0'; i++)
				pl[ind - 1]->name[i] = msg->params[i];
			//printf("name: %s\n", msg->params);

			/*fill struct game*/
			/*for(ind = 0; gm[ind]->command != -1 && \
				ind < MAX_PL;ind++);
			gm[ind]->command = pl->_id;*/
	
			/*for(i=0; pl->name[i] != '\0';i++)
				gm[ind]->params[i]=pl->name[i];*/
			//printf("gm_id=%d\n", gm[ind]->command);
		} 
		//recv(fd[ind]->fd, msg, sizeof(message), 0);//???
		if(msg->command == MSG_SG) {
				int in = 0;
				int id  = atoi(msg->params);
				
				game_args->id1 = pl[ind - 1]->_id;
				game_args->id2 = id;

				thread(game_args);

				while(game_sockd == -1) continue;
				req->command = game_sockd;
				send(fd[ind]->fd, req, sizeof(message), 0);

				i = 0;
							
				/*for(in = 0; id != gm[in]->command &&\
					 gm[in]->command != -1; in++);

				gm[in]->command = -1;
				
				while(gm[in]->params[i] != '\0') {
					gm[in]->params[i] = ' ';
					i++;
				}*/
				del_fds(fd, ind, pl);
			}
			if(msg->command == MSG_RL) {
				req->command = REQ_STARTLIST;
				send(fd[ind]->fd, req, sizeof(message),0);
				for(i = 0; i < MAX_PL; i++) {
					send(fd[ind]->fd, pl[i], sizeof(message),0);
				}
				req->command = REQ_STORLIST;
				send(fd[ind]->fd, req, sizeof(message), 0);
			}
		}


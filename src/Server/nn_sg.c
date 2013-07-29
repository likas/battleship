#include "server.h"

pthread_t threads[thr_max_cnt] = {-1};
//message** gm;


void thread(args *game_arg) {
	int thr_cnt;
	
	for(thr_cnt = 0; thread_id[thr_cnt] > 0 && thr_cnt < thr_max_cnt; thr_cnt++);

	game_arg->thr_cnt = thr_cnt;
	if(pthread_create(&threads[thr_cnt], NULL, Game, game_arg) < 0) {
		perror("error_create_thread");
		exit(1);
	}
}

void nn_sg(message* msg, Player* pl, int ind, struct pollfd *fd) {
	int id = 0, i_pl = 0, i = 0;
	int in = 0, flag = 0;
	printf("NN_SG has been called\n");
	printf("msg.command: %d\n",msg->command);
	printf("msg.params: %s\n",msg->params);
	printf("ind: %d\n", ind);
	message* req=(message*)malloc(sizeof(message));	
	args* game_args = (args*)malloc(sizeof(args));
	game_sockd = -1;
	if(msg->command == MSG_NN) {
			/*send to player the list of gamers*/
			strcpy(pl[ind - 1].name, msg->params);
			recv(fd[ind].fd, req, sizeof(message), 0);
			
			if(req->command == MSG_RL) {
				req->command = REQ_STARTLIST;
				send(fd[ind].fd, req, sizeof(message),0);
				for(i = 0; i < MAX_PL; i++) {
					if(ind - 1 != i)	
						send(fd[ind].fd, (void *)&pl[i], sizeof(message),0);
				}
				req->command = REQ_STOPLIST;
				send(fd[ind].fd, req, sizeof(message), 0);
			}

		} 
		if(msg->command == MSG_SG) {
			int id=(int)(msg->params[0]);
			for(i = 0; pl[i]._id != id; i++);
			printf("Select game\n");
			for(in = 0; in < MAX_PL; in++) {
				if((int)msg->params[0] == pl[in]._id) 
					flag = -1;
			}
			printf("flag: %d\n", flag);
			req->command = REQ_DECLINE;
			if(flag == 0) {
				send(fd[ind].fd,req,sizeof(message),0);
			} else {
				/* send first player accept */
				req->command = REQ_ACCEPT;
				send(fd[ind].fd, req,sizeof(message),0);
				/* send second player  */

				recv(fd[i + 1].fd, req, sizeof(message), 0);
				printf("to player2: %d\n", fd[i + 1].fd);
				printf("req->command: %d\n", req->command);
				printf("req->params: %s\n", req->params);
				
				req->command = REQ_GAMESTARTED;
				strcpy(req->params, pl[ind - 1].name);
				send(fd[i+1].fd, req, sizeof(message), 0);
				
				printf("from player2: %d\n", fd[i + 1].fd);
				printf("req->command: %d\n", req->command);
				printf("req->params: %s\n", req->params);
				
				game_args->id1 = fd[ind].fd;
				game_args->id2 = fd[i+1].fd;
				
				thread(game_args);
				i = 0;
				printf("address of: fds = %p, pl = %p", fd, pl);
				del_fds(fd, ind, pl);
				del_fds(fd, i + 1, pl);
			}}
			if(msg->command == MSG_RL) {
				req->command = REQ_STARTLIST;
				send(fd[ind].fd, req, sizeof(message),0);
				for(i = 0; i < MAX_PL; i++) 
				{
					if(i != ind - 1)
						send(fd[ind].fd, (void*)&pl[i], sizeof(message),0);
				}
				req->command = REQ_STOPLIST;
				send(fd[ind].fd, req, sizeof(message), 0);
			}
		}


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
	//gm = malloc(MAX_PL * sizeof(message*));

	/*while(i < MAX_PL) {i
		gm[i] = malloc(sizeof(message));
		i++;
	}*/
	game_sockd = -1;
	if(msg->command == MSG_NN) {
		
			/*send to player the list of gamers*/
			recv(fd[ind].fd, req, sizeof(message), 0);
			
			if(req->command == MSG_RL) {
				req->command = REQ_STARTLIST;
				send(fd[ind].fd, req, sizeof(message),0);
				for(i = 0; i < MAX_PL; i++) {
					send(fd[ind].fd, (void *)&pl[i], sizeof(message),0);
				}
				req->command = REQ_STORLIST;
				send(fd[ind].fd, req, sizeof(message), 0);
			}

			/*req->command = REQ_STARTLIST;
			printf("Sent %d\n", send(fd[ind]->fd, req, sizeof(message),0));
			for(i = 0; i < MAX_PL; i++) {
				send(fd[ind]->fd, pl[i], sizeof(message),0);
			}
			req->command = REQ_STORLIST;
			send(fd[ind]->fd, req, sizeof(message), 0);
			*/
				/*fill field name in struct Player*/
			/*printf("name = %s:params = %s\n", pl[ind-1].name, msg->params);*/
			//for(i = 0; msg->params[i] != '\0'; i++)
			//	pl[ind - 1]->name[i] = msg->params[i];
			//printf("name: %s\n", msg->params);
			strcpy(pl[ind - 1].name, msg->params);

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


				/*
				 * recv from player
				 * 
				 *
				 *
				 * */
			
				recv(fd[i + 1].fd, req, sizeof(message), 0);
				printf("to player2: %d\n", fd[i + 1].fd);
				printf("req->command: %d\n", req->command);
				printf("req->params: %s\n", req->params);
				
				req->command = REQ_GAMESTARTED;
//				send(fd[message].fd, req,sizeof(message),0);
				send(fd[i+1].fd, req, sizeof(message), 0);
				
				printf("from player2: %d\n", fd[i + 1].fd);
				printf("req->command: %d\n", req->command);
				printf("req->params: %s\n", req->params);

				




				

				game_args->id1 = fd[ind].fd;
				game_args->id2 = fd[i+1].fd;
				
				thread(game_args);

				/*while(game_sockd == -1) continue;
				req->command = game_sockd;
				send(fd[ind].fd, req, sizeof(message), 0);
*/
				i = 0;
							
				/*for(in = 0; id != gm[in]->command &&\
					 gm[in]->command != -1; in++);

				gm[in]->command = -1;
				
				while(gm[in]->params[i] != '\0') {
					gm[in]->params[i] = ' ';
					i++;
				}*/
				printf("address of: fds = %p, pl = %p", fd, pl);
				del_fds(fd, ind, pl);
				del_fds(fd, i + 1, pl);
			}}
			if(msg->command == MSG_RL) {
				req->command = REQ_STARTLIST;
				send(fd[ind].fd, req, sizeof(message),0);
				for(i = 0; i < MAX_PL; i++) {
					send(fd[ind].fd, (void*)&pl[i], sizeof(message),0);
				}
				req->command = REQ_STORLIST;
				send(fd[ind].fd, req, sizeof(message), 0);
			}
		}


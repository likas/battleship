#include"server.h"

int count=0;
//struct pollfd fds[16];//fds-массив структур для poll();
int is_run = 1;

void close_all(struct pollfd *fds){
	int i;
	for(i=0;i<count;i++)
		close(fds[i].fd);
	is_run = 0;
}

void del_fds(struct pollfd *fds,int number,Player *_player){
	printf("address of: fds = %p, pl = %p", fds, _player);
    int i = number;
    while (i < MAX_PL - 1) {
        fds[i] = fds[i+1];
        _player[i-1]._id = _player[i]._id;
        strcpy(_player[i-1].name,_player[i].name);
        i++;
    }
    fds[i].fd = 0;
    fds[i].events = 0;
    _player[i-1]._id = -1;
    strcpy(_player[i-1].name,"");
	--count;
}
int main(int argc, char *argv[]){
	is_run = 1;
	if(argc<2){printf("Not enough arguments"); exit(1);}
	struct pollfd fds[16];//fds-массив структур для poll();
	int ret,i,j,id;//count-счётчик количества элементов в структуре fds;
	struct sockaddr_in servaddr;
    pthread_t thread[MAX_PL];
	Player player[16];
	/*if ( (player = malloc(sizeof(Player)*16)) == NULL){
		printf("error_add_memory\n");
		exit(1);
	}*/
	message msg;
	for(i = 0; i < MAX_PL; i++) {
		player[i]._id = -1;
	}

	port=atoi(argv[1]);
	memset(thread_id,0,16);
//создаём сокет
	if( (fds[count].fd=socket(AF_INET,SOCK_STREAM,0)) < 0){
		perror("Error create socket!");
		exit(1);
	}

	memset(&servaddr,0,sizeof(struct sockaddr_in));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(atoi(argv[1]));

	if(bind(fds[count].fd,(struct sockaddr *)&servaddr,sizeof(struct sockaddr_in))){
		perror("Error bind!");
		exit(1);
	}

	listen(fds[count].fd,16);
	fds[count].events=POLLIN;
	count++;
//ждём каких-либо действий
	while(is_run){
		signal(SIGINT,close_all);
		ret=poll(fds,count,1000);
		if(ret==-1)
			perror("Error poll!");
		if(ret==0)
			continue;
		for(i=0;i<count;i++){
			if(fds[i].revents & POLLIN){
				printf("READ\n");
//если действие произошло по дескриптору главного сокета то обрабатываем подключение клиента
				if(i==0){
                    printf("New Client");
					if( (fds[count].fd=accept(fds[0].fd,0,0)) < 0){
						perror("Error accept!");
					}
					else
					{
						fds[count].events=POLLIN;
						player[count-1]._id=count-1;
						strcpy(player[count-1].name,"");
						count++;
					}
				}else{
					printf("Else\n");
					if( (recv(fds[i].fd,(void *)&msg,sizeof(message),MSG_WAITALL)) <0)
					{
						perror("Error recv!");
						del_fds(fds, i, player);
					}
					else
						nn_sg(&msg,player, i, fds);
				}
			}
		}
	}
	return 0;
}

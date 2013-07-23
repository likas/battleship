#include"server.h"
#include"mboi.h"

int count=0;
struct pollfd fds[16];//fds-массив структур для poll();

void close_all(){
	int i;
	for(i=0;i<count;i++)
		close(fds[i].fd);
	exit(0);
}

int main(int argc, char *argv[]){
	if(argc<2){printf("Not enough arguments"); exit(1);}
	int ret,i,j,id;//count-счётчик количества элементов в структуре fds;
	struct sockaddr_in servaddr;
	pthread_t thread[16];
	Player player[16];
	message msg;

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
	while(1){
		signal(SIGINT,close_all);
		ret=poll(fds,count,100000);
		if(ret==-1)
			perror("Error poll!");
		if(ret==0)
			continue;
		for(i=0;i<count;i++){
			if(fds[i].revents){
				printf("READ\n");
//если действие произошло по дескриптору главного сокета то обрабатываем подключение клиента
				if(i==0){
					if( (fds[count].fd=accept(fds[0].fd,0,0)) < 0){
						perror("Error accept!");
						exit(1);
					}
					player[count-1].id=count-1;
					strcpy(player[count-1].name,"");
					count++;
				}else{
					if( (recv(fds[i].fd,(void *)&msg,sizeof(message),0)) <0){
						perror("Error recv!");
						exit(1);
					}
					nn_sg(msg,player,&fds[i].fd);
				}
			}
		}
	}
	return 0;
}








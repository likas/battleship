#include "for_fork.h"
#define BUFLEN 81

int childWork(int sockClient){
    char buf[BUFLEN];
    int magLenght;
    bzero(buf,BUFLEN);
    if ( (magLenght = recv(sockClient, buf, BUFLEN, 0)) < 0){
        perror("");
        return 1;
    }
    printf("SERVER: SOCKET - %d\n",sockClient);
    printf("SERVER: Lenght - %d\n",magLenght);
    printf("SERVER: Send:%s\n\n",buf);
}

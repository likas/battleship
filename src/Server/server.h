#ifndef SERVER_H
#define SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/poll.h>
#include "../mboi.h"
#include "for_fork.h"
#include <unistd.h>

int childWork(int sockClient);
void* Game(void*);

typedef struct {
    int _id;
    char name[30];
}Player;

int port;
int thread_id[50];
int game_sockd;

#endif

#ifndef INCLUDE_FOR_FORK
#define INCLUDE_FOR_FORK
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
int childWork(int sockClient);
typedef struct {
    int TYPE_COMMAND;
    char command[128];
}Command;
typedef struct {
    int _id;
    char name[20];
}Player;
#endif

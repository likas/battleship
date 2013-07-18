#ifndef CLIENT_H
#define CLIENT_H
/*----------------------*/
#define size 10
/*----------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../mboi.h"
/*----------------------*/
typedef struct _shot
{
    int x;
    int y;
}shot;
/*----------------------*/
#endif

int ser_soc;

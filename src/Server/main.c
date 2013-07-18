#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include "for_fork.h"
#include <stdlib.h>
#include <strings.h>
#define MAX_PLAYERS 10

int main(int argc,char *argv[])
{
    int PORT;
    int sockMain,sockClient,lenght,child;
    struct sockaddr_in servAddr;
    struct pollfd fds[MAX_PLAYERS];
    /* Определение порта */

    if ( ( argc > 1) && ( atoi(argv[1]) != 0 )){
        PORT = atoi(argv[1]);
        printf("PORT = %d\n",PORT);
    } else {
        PORT = 7777;
        printf("PORT = %d\n",PORT);
    }

    /* Главный сокет
     *
     */
     printf("0\n");
    if ((sockMain = socket(AF_INET,SOCK_STREAM , 0)) < 0){
        perror("Сервер не может открыть сокет");
        return 1;
    }
    printf("1\n");
    /*  Структура для хранения данных
     *
     *
     */
    bzero( (char *) &servAddr ,sizeof (servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(PORT);
    /* Связывание запроса
     *
     */
    printf("2\n");
    if ( bind(sockMain ,(struct sockaddr *)&servAddr ,sizeof(struct sockaddr)) < 0 ){
        perror("Нет связи");
        return 1;
    }
    printf("2\n");
    lenght = sizeof(servAddr);

    /*  Создание очереди для 10 клиентов
     */
    listen(sockMain, 10);
    /*  Ждем клиента
     */
    for ( ; ; ) {
        printf("3\n");
        if ( (sockClient = accept(sockMain,0,0)) < 0 ){
            perror("Неверный сокет клиента");
            return 1;
        }
        printf("4\n");
        /*  Создание дочернего процесса
         */
        if ( (child = fork()) < 0){
            perror("Ошибка создания дочернего процесса");
            return 1;
        } else if (child==0) {
            close(sockMain);
            childWork(sockClient);
            close(sockClient);
            return 0;
        }

        close(sockClient);

    }
    return 0;
}


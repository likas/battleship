#ifndef GUI_H
#define GUI_H
#define _GNU_SOURCE

#include "../mboi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>
#include <menu.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include <signal.h>

WINDOW*** my_win;
WINDOW*** op_win;
WINDOW* chat;
WINDOW* info;


int **MY;
int **OP;

//Is blocking multithreading flag
int SIZEFLAG;

int GUICHATLEN;//служебная переменная для листинга чата
char username[100];//ник игрока
char opname[100];//ник противника
struct pair {int x; int y; }; //структура для возврата пары координат массива
//typedef struct {int command; char params[128]; } message;


int gui();
 //общая инициализация
void guiturn(int,int);
void endgui(int);
void FINref(WINDOW*, int, int);
//очистка окна. Первый аргумент окно которое нужно очистить, второй номер цветовой пары, третий флаг 0 или 1, 0 - очистить вместе с содержимым окна
//1-просто обновить окно
int FINchat(char*,char*,int);
//посылка сообщения в чат. Первый аргумент - имя того кто посылает, второй - сообщение,
// 3й- обязательный параметр GUICHATLEN ( вызов функции должен быть вида  GUICHATLEN=FINchat(*,*,GUICHATLEN) )

void FINchcell(int, int,int,int);
 //Изменение состояния ячейки. Первые 2 аргумента координаты ячейки x y. Третий-номер цвета. Четвертый- флаг: 0-ячейка в нашем поле, 1-в поле противника

void Fscroll(WINDOW*, int, int);

int De_Init(int **, int **);
void render(int**,int**,int);
//Рисовка полей, подаются 2 массива представляющих из себя поля.

COORDS  De_Move(int**);
 //Наш ход, подается массив поля противника

void ant_hello(char* , char*);
//Приветствие

char* ant_login(int);
//Присваивание имени игроку
int ant_player_list(message* , int);
//листинг списка игроков

int show_menu();
#endif

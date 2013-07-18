#ifndef H_MBOI
#define H_MBOI
#include <stdlib.h>
int const SIZE = 10;
int const COUNT_SHIP = 4
#define MSG_LEN 128

enum _CELL_STATE
{
	CELL_NONE,
	CELL_SHIP,
	CELL_SHIP_FIRE,
	CELL_SHIP_DEAD,
	CELL_MISS
} CELL_STATE;

enum _KEY
{
	KEY_LEFT, 
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_SPACE,
	KEY_ENTER,
	KEY_TAB,
	KEY_ESC
} KEY;

enum _REQUESTS
{
	REQ_ACCEPT,
	REQ_DECLINE,
	REQ_HIT,
	REQ_MISS,
	REQ_DESTROYED,
	REQ_YOUWIN,
	REQ_YOULOSE,
	REQ_DISCONNECT,
	REQ_STARTLIST,
	REQ_STORLIST,
	REQ_GAMESTARTED
} REQ;

typedef struct{
	int command;
	char params[128];
} message;

enum _MSG_TSK
{
	MSG_NN,//ник
	MSG_RQ,//ответ сервера
	MSG_TT,//сообщение чата
	MSG_AT,//атака
	MSG_HM,//попадание
	MSG_SG//начало игры
} MSG_TSK;

typedef struct _COORDS
{
	int x;
	int y;
} COORDS;
#endif

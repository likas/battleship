#ifndef H_MBOI
#define H_MBOI

#ifndef SIZE
#define SIZE 10
#endif

#ifndef COUNT_SHIP
#define COUNT_SHIP 4
#endif

#ifndef MSG_LEN
#define MSG_LEN 128
#endif 
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

//Select game with ai or other client
int GAME_WITH_AI;

enum _CELL_STATE
{
	CELL_NONE = 2,
	CELL_SHIP,
	CELL_SHIP_FIRE,
	CELL_MISS, 
	CELL_SHIP_DEAD
} CELL_STATE;

enum _KEY
{
	KEY_LEFT = 10, 
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
	REQ_ACCEPT = 20,
	REQ_DECLINE,
	REQ_HIT,
	REQ_MISS,
	REQ_DESTROYED,
	REQ_YOUWIN,
	REQ_YOULOSE,
	REQ_DISCONNECT,
	REQ_NDISCONNECT,
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
	MSG_NN = 40, /* ник */
	MSG_RQ,		 /* ответ сервера */
	MSG_TT,		 /* сообщение чата */
	MSG_AT,		 /* атака */
	MSG_HM,		 /* попадание */
	MSG_SG,		 /* начало игры */
	MSG_SF,		 /* Начало передачи поля */
	MSG_RL
} MSG_TSK;

typedef struct 
{
	int x;
	int y;
} COORDS;
enum _GAMERS 
{
  ENEMY = 100,
  PLAYER
} GAMERS;

enum _MENU_VAR
{
	MULTI_R,
 	MULTI,       
 	SINGLE_R,   
    SINGLE,     
    BACK,        
    QUIT        
} MENU_VAR;
#endif

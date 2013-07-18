int SIZE = 10;
#define MSG_LEN 128
enum _CELL_STATE
{
	NONE,
	SHIP,
	SHIP_FIRE,
	SHIP_DEAD,
	MISS
} CELL_STATE;

enum _KEY
{
	LEFT, 
	RIGHT,
	UP,
	DOWN,
	SPACE,
	ENTER,
	TAB,
	ESC
} KEY;

enum _REQUESTS
{
	ACCEPT,
	DECLINE,
	HIT,
	MISS,
	DESTROYED,
	YOUWIN,
	YOULOSE,
	DISCONNECT,
	STARTLIST,
	STORLIST,
	GAMESTARTED
} REQ;

typedef struct{
	int command;
	char params[128];
} message;

enum _MSG_TSK
{
	NN,//ник
	RQ,//ответ сервера
	TT,//сообщение чата
	AT,//атака
	HM,//попадание
	SG//начало игры
} MSG_TSK;

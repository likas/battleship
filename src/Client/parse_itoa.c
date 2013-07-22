#include "client.h"
int parser_itoa(int number, char* buf){
	int i,b,r;
	b=number;r=0;
	while(b>0)
	{
		r++;
		b/=10;
	}
	b=number;
	char buf[r];
	i=0;
	while (b>0)
	{
		buf[i]=b%10;
		b/=10;
	}
	return 0;
}

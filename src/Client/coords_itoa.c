#include "../mboi.h"
/* #include "client.h" */
int coords_itoa(char* array, COORDS *xy){
	xy->x=array[0];
	xy->y=array[1];
	return 0;
}

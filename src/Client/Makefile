SOURCES=socket_init.c client_send_text.c go_list.c client_send_attack.c coords_itoa.c coords_atoi.c with_ai.c map.c
OBJ=$(SOURCES:.c=.o)
MAIN=client.c
HEADER=client.h
KEYS=-std=c99 -Wall -pedantic -g 
all: $(MAIN) libClient.a
	gcc $(KEYS) $(MAIN) -o cl -L. -lClient -L../GUI/ -lgui -L../AI/ -lAI -lncurses
libClient.a: $(OBJ)
	ar cr libClient.a $(OBJ) 
%.o:%.c
	gcc $(KEYS) -c $*.c -o $*.o

clear:
	rm *.o *.a cl

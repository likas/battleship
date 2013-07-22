SOURCES=socket_init.c client_send_text.c go_list.c client_send_attack.c coords_itoa.c coords_atoi.c with_ai.c
OBJ=$(SOURCES:.c=.o)
MAIN=client.c
HEADER=client.h
KEYS=-Wall -pedantic -g
all: $(MAIN) libClient.a
	gcc $(KEYS) $(MAIN) -o cl -L. -lClient -L ../GUI/ -L ../AI/ -lgui -lncurse -lai
libClient.a: $(OBJ)
	ar cr libClient.a $(OBJ) 
%.o:%.c
	gcc -c $*.c -o $*.o

clear:
	rm *.o *.a

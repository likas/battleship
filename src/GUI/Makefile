sources:=gui.c ref.c chat.c render.c De_Init.c hello.c chcell.c endgui.c De_Move.c login.c scroll.c listing.c
obj:=$(sources:.c=.o)
main=main.c
headers=gui.h
path=~/20l

all:  $(obj) $(headers)
	ar cr libgui.a $(obj)
	ranlib libgui.a
	gcc $(main) -L. -lgui -lncurses -o gui 
%.o:%.c
	gcc -c $*.c -o $*.o	
backup:
	cp red.c  /home/2013/finiks/backup/13l
	cp ref.o /home/2013/finiks/backup/13l/
	cp ref.c /home/2013/finiks/backup/13l/
	cp opfile.o /home/2013/finiks/backup/13l/
	cp opfile.c /home/2013/finiks/backup/13l/
	cp redfile.o /home/2013/finiks/backup/13l/
	cp redfile.c /home/2013/finiks/backup/13l/
	cp red.h /home/2013/finiks/backup/13l/
	cp Makefile /home/2013/finiks/backup/13

clean:
	rm -f *.o
	

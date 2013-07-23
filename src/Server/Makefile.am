AUTOMAKE_OPTIONS = foreign

AM_LDFLAGS = -ldl
AM_CFLAGS = -std=c99 -L../include -lGUI -lpthread

bin_PROGRAMS = Server
Server_SOURCES =		\
game.c					\
for_fork.c				\
server.c				\
thread_server.c

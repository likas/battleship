#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Battleships], [1,0], [kostiamalikov@gmail.com])
AM_INIT_AUTOMAKE
#AC_CONFIG_SRCDIR([Client/client.c] [Server/server.c])
AC_CONFIG_HEADERS([config.h:config.in])

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL
ACLOCAL_AM_FLAGS
# Checks for libraries.
# FIXME: Replace `main' with a function in `-lClient':

# FIXME: Replace `main' with a function in `-lgui':

# FIXME: Replace `main' with a function in `-lncurses':
AC_CHECK_LIB([ncurses], [main])
AC_CHECK_LIB([gui], [main])
AC_CHECK_LIB([Client], [main])
# Checks for header files.
AC_CHECK_HEADERS([netdb.h netinet/in.h stdlib.h string.h strings.h sys/ioctl.h sys/socket.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([bzero inet_ntoa memset socket])

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_FILES([Makefile]
				[src/AI/Makefile]
				[src/Client/Makefile]
				[src/GUI/Makefile]
				[src/Server/Makefile])
#AC_CONFIG_SUBDIRS([AI])
AC_OUTPUT

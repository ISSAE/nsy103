SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_fork		\
		exemple_getgroups	\
		exemple_getpgid		\
		exemple_getpgrp		\
		exemple_getsid		\
		exemple_getuid		\
		exemple_setgroups	\
		exemple_setreuid	\
		exemple_setresgid	\
		exemple_setresuid	\
		exemple_setuid

all : ${EXECUTABLES}

clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}

SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_execlp		\
		exemple_execv		\
		exemple_execve		\
		exemple_execvp		\
		exemple_popen_1		\
		exemple_popen_2		\
		exemple_popen_3		\
		exemple_system		\

all : ${EXECUTABLES}

clean : 
	@rm -f core *.o a.out
	@rm -f ${EXECUTABLES}

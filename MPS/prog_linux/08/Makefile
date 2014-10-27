SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_siginfo		\
		exemple_sigqueue	\
		exemple_sigqueue_1	\
		exemple_sigtimedwait	\
		exemple_sigwaitinfo	\

all : ${EXECUTABLES}

clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}

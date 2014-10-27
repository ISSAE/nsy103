SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_clock		\
		exemple_getrlimit	\
		exemple_nanosleep	\
		exemple_rusage		\
		exemple_setitimer_1	\
		exemple_setitimer_2	\
		exemple_setitimer_3	\
		exemple_setrlimit	\
		exemple_sleep		\
		exemple_times_1		\
		exemple_times_2		\
		exemple_usleep		\

all : ${EXECUTABLES}

clean : 
	@rm -f core *.o a.out
	@rm -f ${EXECUTABLES}

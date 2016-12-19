SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_siginterrupt	\
		exemple_signal		\
		exemple_signal_2	\
		exemple_signal_3	\
		exemple_strsignal

all : ${EXECUTABLES}

clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}

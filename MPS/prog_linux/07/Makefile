SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_alarm		\
		exemple_fatal		\
		exemple_sigaction_1	\
		exemple_sigaction_2	\
		exemple_sigaction_3	\
		exemple_sigaltstack	\
		exemple_siglongjmp	\
		exemple_sigpending	\

all : ${EXECUTABLES}

clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}

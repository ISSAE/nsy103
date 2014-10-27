SHELL=/bin/sh

CFLAGS = -Wall -g -pedantic

EXECUTABLES=	exemple_readlink	\
		exemple_stat		\
		exemple_tailles		\
		exemple_truncate	\
		exemple_umask		\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}

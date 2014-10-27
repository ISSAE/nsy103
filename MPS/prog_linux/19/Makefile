SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_dup		\
		exemple_fcntl		\
		exemple_fcntl_2		\
		exemple_fcntl_3		\
		exemple_fcntl_4		\
		exemple_fcntl_5		\
		exemple_lseek		\
		exemple_mon_write	\
		exemple_open		\
		exemple_open_2		\
		exemple_open_3		\
		exemple_write		\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}

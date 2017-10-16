SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_assert		\
		exemple_atexit		\
		exemple_exit_1		\
		exemple_exit_2		\
		exemple_on_exit		\
		exemple_perror		\
		exemple_strerror	\
		exemple_sys_errlist	\
		exemple_wait_1		\
		exemple_wait_2		\
		exemple_wait_3		\
		exemple_zombie_1	\
		exemple_zombie_2

all : ${EXECUTABLES}

clean : 
	@rm -f core *.o a.out
	@rm -f ${EXECUTABLES}

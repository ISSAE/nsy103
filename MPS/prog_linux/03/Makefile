SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_argv		\
		exemple_environ		\
		exemple_environ_2	\
		exemple_getenv		\
		exemple_getopt		\
		exemple_getopt_long	\
		exemple_options		\
		exemple_putenv

all : ${EXECUTABLES}

exemple_options : exemple_options.c
	cc ${CFLAGS} -D_GNU_SOURCE exemple_options.c -o exemple_options

clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}

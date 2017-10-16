SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_alloca			\
		exemple_calloc_1		\
		exemple_calloc_2		\
		exemple_calloc_3		\
		exemple_hook			\
		exemple_hook_2			\
		exemple_malloc_1		\
		exemple_malloc_2		\
		exemple_mcheck_1		\
		exemple_mcheck_2		\
		exemple_memoire			\
		exemple_mtrace_1		\
		exemple_mtrace_2		\


all : ${EXECUTABLES}

clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}

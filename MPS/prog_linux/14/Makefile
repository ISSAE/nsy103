SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	cree_gros_fichier		\
		exemple_mmap_1			\
		exemple_mmap_2			\
		exemple_mprotect_1		\
		exemple_mprotect_2		\


all : ${EXECUTABLES}

clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}

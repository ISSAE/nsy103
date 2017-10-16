SHELL=/bin/sh

CFLAGS = -Wall -g -pedantic -lgdbm

EXECUTABLES=	cherche_cle_dbm		\
		cherche_nom_dbm		\
		cherche_nom_ndbm	\
		cree_dbm		\
		exemple_dbopen		\
		parcours_dbm		\
		parcours_gdbm		\
		parcours_ndbm		\

all : ${EXECUTABLES}

exemple_dbopen: exemple_dbopen.c
	cc -Wall -g -o exemple_dbopen -ldb1 exemple_dbopen.c

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}

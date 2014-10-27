SHELL=/bin/sh

CFLAGS = -Wall -g -pedantic

EXECUTABLES=	exemple_chroot		\
		exemple_fchdir		\
		exemple_fnmatch		\
		exemple_glob		\
		exemple_mkdir		\
		exemple_nftw		\
		exemple_opendir		\
		exemple_realpath	\
		exemple_remove		\
		exemple_scandir		\
		exemple_temp		\
		exemple_unlink		\
		exemple_wordexp		\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}

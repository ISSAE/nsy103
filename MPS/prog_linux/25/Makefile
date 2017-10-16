SHELL=/bin/sh

CFLAGS = -Wall -g -pedantic -lm

EXECUTABLES=	exemple_ctime			\
		exemple_getdate			\
		exemple_gettimeofday		\
		exemple_localtime		\
		exemple_strftime		\
		exemple_strptime		\
		exemple_tzname			\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}

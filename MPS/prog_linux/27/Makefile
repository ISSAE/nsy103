SHELL=/bin/sh

CFLAGS = -Wall -g -pedantic -lm

EXECUTABLES=				\
		exemple_catgets		\
		exemple_gettext		\
		exemple_localeconv	\
		exemple_nl_langinfo	\
		exemple_numeric		\
		exemple_setlocale	\
		exemple_strfmon		\
		exemple_strfmon_2	\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}

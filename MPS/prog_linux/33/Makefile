SHELL=/bin/sh

CFLAGS = -Wall -g

EXECUTABLES=				\
		client_pty		\
		exemple_flush		\
		exemple_getpass		\
		exemple_isatty		\
		exemple_pty		\
		exemple_raw		\
		exemple_serie		\
		exemple_socket		\
		serie_2_stdout		\
		stdin_2_serie		\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}

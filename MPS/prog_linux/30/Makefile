SHELL=/bin/sh

CFLAGS = -Wall -g -pedantic -lrt -lpthread

EXECUTABLES=				\
		exemple_aio_read	\
		exemple_aio_suspend	\
		exemple_async		\
		exemple_lio_listio	\
		exemple_nonblock_1	\
		exemple_nonblock_2	\
		exemple_osync		\
		exemple_select		\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}

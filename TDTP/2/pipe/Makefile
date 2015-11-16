
PROGS =	mainpipe mainpopen mainfifo \
		client_fifo server_fifo pipeconf test1 test2 fduplex

all:	${PROGS}

mainpipe:	mainpipe.o client.o server.o
		${CC} ${CFLAGS} -o $@ mainpipe.o client.o server.o 

mainpopen:	mainpopen.o
		${CC} ${CFLAGS} -o $@ mainpopen.o 

mainfifo:	mainfifo.o client.o server.o
		${CC} ${CFLAGS} -o $@ mainfifo.o client.o server.o 

client_fifo:	client_main.o client.o
		${CC} ${CFLAGS} -o $@ client_main.o client.o 

server_fifo:	server_main.o server.o
		${CC} ${CFLAGS} -o $@ server_main.o server.o 

pipeconf:	pipeconf.o
		${CC} ${CFLAGS} -o $@ pipeconf.o 

test1:	test1.o
		${CC} ${CFLAGS} -o $@ test1.o 

test2:	test2.o
		${CC} ${CFLAGS} -o $@ test2.o

fduplex:	fduplex.o
		${CC} ${CFLAGS} -o $@ fduplex.o 

clean:
		rm -f ${PROGS} ${CLEANFILES}

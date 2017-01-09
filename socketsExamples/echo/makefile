all: echoSrv echoSrvThread echoCli

echoSrvThread: echoSrvThread.c serviceEcho.c wrsock.o
	gcc -Wall -o $@ echoSrv.c serviceEcho.c wrsock.o -lpthread

echoSrv: echoSrv.c serviceEcho.c wrsock.o
	gcc -Wall -o $@ echoSrv.c serviceEcho.c wrsock.o -lpthread

echoCli: echoCli.c wrsock.o
	gcc -Wall -o $@ echoCli.c wrsock.o

wrsock.o: ../lib/wrsock.c ../lib/wrsock.h 
	gcc -Wall -c $<

clean:
	rm wrsock.o echoCli echoSrv

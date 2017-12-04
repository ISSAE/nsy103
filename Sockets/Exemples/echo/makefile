all: echoSrv echoSrvThread echoCli

echoSrvThread: echoSrvThread.c serviceEcho.c helperSO.o
	gcc -Wall -o $@ echoSrv.c serviceEcho.c helperSO.o -lpthread

echoSrv: echoSrv.c serviceEcho.c helperSO.o
	gcc -Wall -o $@ echoSrv.c serviceEcho.c helperSO.o

echoCli: echoCli.c helperSO.o
	gcc -Wall -o $@ echoCli.c helperSO.o

helperSO.o: ../helper/helperSO.c ../helper/helperSO.h
	gcc -Wall -c $<

clean:
	rm helperSO.o echoCli echoSrv

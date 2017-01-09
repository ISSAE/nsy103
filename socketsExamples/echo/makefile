all: echoSrv echoCli

echoSrv: echoSrv.c wrsock.o
	gcc -o $@ echoSrv.c wrsock.o

echoCli: echoCli.c wrsock.o
	gcc -o $@ echoCli.c wrsock.o

wrsock.o: ../lib/wrsock.c ../lib/wrsock.h 
	gcc -c $<

clean:
	rm wrsock.o echoCli echoSrv

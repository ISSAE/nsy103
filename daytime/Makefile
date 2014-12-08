all: serv cli

serv: o/wrsock.o o/server.o
	    gcc -o dist/serv o/wrsock.o o/server.o
	
cli: o/wrsock.o o/client.o
	gcc -o dist/cli o/wrsock.o o/client.o
	
o/wrsock.o: wrsock.c wrsock.h
	gcc -o o/wrsock.o -c -Wall wrsock.c
	
o/client.o: client.c wrsock.h
	gcc -o o/client.o -c -Wall client.c
	
o/server.o: server.c wrsock.h
	gcc -o o/server.o -c -Wall server.c
	
clean:
	rm o/* dist/*
	
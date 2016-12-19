all: serv cli

serv: o/traitement.o o/wrsock.o o/server.o
	    gcc -o dist/serv o/traitement.o o/wrsock.o o/server.o
	
cli: o/wrsock.o o/client.o
	gcc -o dist/cli o/wrsock.o o/client.o
	
o/traitement.o: traitement.c traitement.h
	gcc -o o/traitement.o -c -Wall traitement.c

o/wrsock.o: wrsock.c wrsock.h
	gcc -o o/wrsock.o -c -Wall wrsock.c
	
o/client.o: client.c wrsock.h
	gcc -o o/client.o -c -Wall client.c
	
o/server.o: server.c wrsock.h
	gcc -o o/server.o -c -Wall server.c
	
clean:
	rm o/* dist/*
	

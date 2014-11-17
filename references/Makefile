
monpremier: main.o premier.o
	gcc -o monpremier main.o premier.o

main.o: main.c premier.h
	gcc -c main.c

premier.o: premier.c premier.h
	gcc -c premier.c

clean:
	rm *.o

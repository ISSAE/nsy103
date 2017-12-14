prodCons: producteurConsomateur.c BufferCirc.o
	gcc -o prodCons producteurConsomateur.c BufferCirc.o -lpthread

BufferCirc.o: BufferCirc.c BufferCirc.h
	gcc -c BufferCirc.c

clean:
	rm prodCons BufferCirc.o
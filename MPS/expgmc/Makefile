main: main.c ldmain.a
	gcc -o $@ main.c ldmain.a 

ldmain.a: min.o maj.o
	ar r ldmain.a min.o maj.o

clean: 
	rm main ldmain.a *.o

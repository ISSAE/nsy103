
#compilation avec warning strict pour eviter les bugs
CFLAGS=-Wall -pedantic

#Compilation avec debuging
#CFLAGS=-D DEBUG -Wall -pedantic
	
lance : utiliseRefFonc.c fadd.o fmult.o applyOps.o signatures.h
	gcc $(CFLAGS) -o $@ utiliseRefFonc.c fadd.o fmult.o applyOps.o

clean :
	rm *.o lance
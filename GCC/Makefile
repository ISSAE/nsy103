useDouble.c: useDoubleAdd.c
	cp useDoubleAdd.c useDouble.c

useDouble.o: useDouble.c afficheA.h
	gcc -c useDouble.c -o useDouble.o

%.o: %.c
	echo "From $@ to $< ?"
	gcc -c $< -o $@

monpremierpgm: afficheA.o useDouble.o
	gcc afficheA.o useDouble.o -o monpremierpgm

clean:
	rm *.o monpremierpgm

all: testStruct testAffectStruct testVect

testStruct: struct.c
	gcc -o $@ struct.c

testAffectStruct: teststruct.c
	gcc -o $@ teststruct.c

vect.o: vect.c vect.h
	gcc -c $<

testVect: testVect.c vect.o vect.h
	gcc -o $@ testVect.c vect.o

clean:
	rm *.o testStruct testVect testAffectStruct



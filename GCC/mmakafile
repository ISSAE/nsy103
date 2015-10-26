premierPgm.i: premierPgm.c
	gcc -E $< -o $@


%o: %.c
	echo "From $@ to $< ?" 

%.i: %.c
	gcc -E $< -o $@

%.s: %.i
	gcc -S $< -o $@

%.o: %.s
	gcc -c $< -o $@

clean:
	rm *.o *.s *.i

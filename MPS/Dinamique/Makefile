CFLAGS = -Wall 
LDFLAGS = -g
CC = gcc

TARGETS = usehello loadhello

all: $(TARGETS) 


libhello.o: libhello.c
	@echo "*  utilisez -fPIC pour construire un objet pour library partagée."
	gcc -fPIC $(CFLAGS) -c $<

libhello.so.0.0:	libhello.o
	@echo "*  Link libhello against libc for best results on all systems."
	gcc $(LDFLAGS) -shared -Wl,-soname,libhello.so.0 -o $@ $< -lc
	@echo "*  Création du fichier dont le nom correspond au soname"
	ln -sf libhello.so.0.0 libhello.so.0
	@echo "*  Créarion de libhello.so pour utiliser le liker -lhello."
	ln -sf libhello.so.0 libhello.so

usehello: usehello.o libhello.so.0.0
	@echo "*  -L. -lhello, pas libhello.so.0!"
	gcc $(LDFLAGS) -o $@ $< -L. -lhello
	@echo "*  executer en faisant: LD_LIBRARY_PATH=`pwd` ./$@"

loadhello: loadhello.o libhello.so.0.0
	gcc $(LDFLAGS) -o $@ $< -ldl
	@echo "executer en: LD_LIBRARY_PATH=`pwd` ./$@"


clean:
	rm -f $(TARGETS) *.o libhello.so*


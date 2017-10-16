SHELL=/bin/sh

CFLAGS = -Wall -pedantic -g

EXECUTABLES=	exemple_crypt			\
		exemple_crypt_2			\
		des_crypte			\
		des_decrypte			\
		exemple_ecb_crypt		\
		exemple_regcomp			\
		exemple_strfry			\


all : ${EXECUTABLES}

exemple_crypt : exemple_crypt.c
	cc -Wall -g exemple_crypt.c -o exemple_crypt -lcrypt

exemple_crypt_2 : exemple_crypt_2.c
	cc -Wall -g exemple_crypt_2.c -o exemple_crypt_2 -lcrypt

des_crypte :
	ln -sf exemple_ecb_crypt des_crypte

des_decrypte :
	ln -sf exemple_ecb_crypt des_decrypte


clean : 
	@rm -f core *.o *.out
	@rm -f ${EXECUTABLES}

SHELL=/bin/sh

CFLAGS = -Wall -g 

EXECUTABLES=					\
		delai_close			\
		exemple_client_anagramme	\
		exemple_demon_anagramme		\
		exemple_inet_anagramme		\
		exemple_reception_multicast	\
		exemple_serveur_anagramme	\
		exemple_serveur_daytime		\
		exemple_serveur_tcp		\
		stdin_2_udp			\
		tcp_2_stdout			\
		udp_2_stdout			\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}

SHELL=/bin/sh

CFLAGS = -Wall -g -pedantic -lm

EXECUTABLES=	exemple_fstab			\
		exemple_getdomainname		\
		exemple_gethostname		\
		exemple_getutent		\
		exemple_hasmntopt		\
		exemple_mtab			\
		exemple_statfs			\
		exemple_sysinfo			\
		exemple_syslog			\
		exemple_uname			\
		exemple_utmpname		\


all : ${EXECUTABLES}

clean : 
	@rm -f core* *.o *.out essai.*
	@rm -f ${EXECUTABLES}

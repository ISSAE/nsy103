SUBDIRS	=    02 03 04 05 06 07 08 09 10 	\
	  11 12 13 14 15 16 17 18 19 20 	\
	  21 22 23 24 25 26 27 28 29 30 	\
	  31 32 33

clean: 
	@set -e; \
	for i in $(SUBDIRS); \
	do \
		cd $$i; \
		make clean; \
		cd ..; \
	done

all: 
	@set -e; \
	for i in $(SUBDIRS); \
	do \
		cd $$i; \
		make all ; \
		cd ..; \
	done



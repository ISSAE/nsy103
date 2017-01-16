#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
main () {
	mode_t mode;
	int tub;
	mode = S_IRUSR | S_IWUSR;
	/*création du tube nommé */
	mkfifo ("fictub", mode);
	/* ouverture du tube */
	tub = open ("fictub", O_WRONLY);
	/* écriture dans le tube */
	write (tub, "0123456789", 10);
	/* fermeture du tube */
	close(tub);
}

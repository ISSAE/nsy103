#include	"unpipc.h"
#define MAXLINE 100
void
server(int readfd, int writefd)
{
	int		fd;
	ssize_t	n;
	char	buff[MAXLINE+1];

	/* lecture du canal IPC (Inter Process Communication) */
	if ( (n = read(readfd, buff, MAXLINE)) == 0)
		perror("end-of-file while reading pathname");
	buff[n] = '\0';		/* une chaine en C se termine par NULL */

	if ( (fd = open(buff, O_RDONLY)) < 0) {
			/* error: avertir le client */
		snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n",
				 strerror(errno));
		n = strlen(buff);
		write(writefd, buff, n);

	} else {
			/* 4open succé: copy file to IPC channel */
		while ( (n = read(fd, buff, MAXLINE)) > 0)
			write(writefd, buff, n);
		close(fd);
	}
}

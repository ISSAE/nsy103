/*
 * daytime-client-udp - a simple UDP client
 *
 * Programmed by Johan Kuuse
 * January 30, 2007
 */
#include <sys/types.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

#include "numcheck.h"

#define MAXBUFLEN 100

int
main(int argc, char *argv[])
{
  register int sfd;
  int addr_len;
  struct sockaddr_in server_addr;
  int numbytes;
  char buf[MAXBUFLEN];
  char usage[LINE_MAX];
  int portnumber;
  const int portnumberdefault = 13;

  /* Usage message. */
  sprintf(usage, "Usage: %s [portnumber] (0 <= port_number <= 65535)\nExample: %s 1024\n", argv[0], argv[0]);

  /* Check command line arg. */
  switch (argc)
    {
    case 1:
      /* No arguments - use default port number. */
      portnumber = portnumberdefault;
      break;
    case 2:
      /* Set port number from argument. */
      if (argtol((long *)&portnumber, argv[1], usage))
        return 2;
      if (rangecheck(portnumber, 0, 65535, 1, usage))
        return 3;
      break;
    default:
      printf("%s", usage);
      return 1;
    }

  /* Sequence of system calls for a UDP (connectionless state) client:                                        */
  /*   socket()   */
  /*   sendto()   */
  /*   fcntl()    */
  /*   recvfrom() */
  /*   close()    */

  /* Set protocol to "0" to have socket() choose the correct protocol. */
  if ((sfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror("socket");
      return 4;
    }

  /* Prepare the socket address struct. */
  server_addr.sin_family      = AF_INET;
  server_addr.sin_port        = htons(portnumber);
  /* Talk to all interfaces. */
  server_addr.sin_addr.s_addr = INADDR_ANY;
  /* Talk to an interface with a specific IP (requires <arpa/inet.h>). */
  /* inet_aton("127.0.0.1", &(server_addr.sin_addr)); */
  /* Zero the rest of the struct. */
  memset(&(server_addr.sin_zero), '\0', 8);

  addr_len we want data. */
  if ((sendto(sfd, "", 0, 0, (struct sockaddr *)&server_addr, addr_len)) < 0)
    {
      perror("daytimed-udp send");
      close(sfd);
      return 5;
    }

  /* Hack:  */
  /*   Make this socket nonblocking with fcntl().  */
  /*   We expect data to be available immediately.  */
  /*   If not, we assume that the UDP server is not running, or got stuck.  */
  /*   (It would be better to wait a limited time for data to arrive, using select().) */
  /*   This hack avoids the the UDP client (this program) to hang if the UDP server hasn't been started. */
  /* Make this socket nonblocking.  */
  if (fcntl(sfd, F_SETFL, O_NONBLOCK) == -1)
    {
      perror("fcntl");
      close(sfd);
      return 6;
    }

  /* Receive the answer from the server. */
  if ((numbytes = recvfrom(sfd, buf, (int)sizeof(buf) , 0, NULL, &addr_len)) < 0)
    {
      perror("recvfrom");
      if (errno == EAGAIN)
        {
          printf("Check that the server is running on the port you are trying to connect to (port %d).\n", portnumber);
        }
      close(sfd);
      return 7;
    }

  /* Null-terminate the message so we can print it as a string.  */
  buf[numbytes] = '\0';
  printf("%s",buf);

  /* Close the socket. */
  close(sfd);

  return 0;
}

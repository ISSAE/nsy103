/*
 * daytime-server-udp - a simple UDP server
 *
 * Programmed by Johan Kuuse
 * January 30, 2007
 */
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "numcheck.h"

#define BACKLOG 4
#define MAXBUFLEN 100

int
main(int argc, char *argv[])
{
  register int sfd;
  int addr_len;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  time_t t;
  struct tm *tm;
  int numbytes;
  char usage[LINE_MAX];
  char timemsg[LINE_MAX];
  char buf[MAXBUFLEN];
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
        return 1;
      if (rangecheck(portnumber, 0, 65535, 1, usage))
        return 1;
      break;
    default:
      printf("%s", usage);
      return 1;
    }

  /* Sequence of system calls for a UDP (connectionless state) server:                                        */
  /*   socket()   */
  /*   bind()     */ 
  /*   recvfrom() */
  /*   sendto()   */
  /*   close()    */

  /* Set protocol to "0" to have socket() choose the correct protocol. */
  if ((sfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror("socket");
      return 1;
    }

  /* Prepare the server address struct. */
  server_addr.sin_family      = AF_INET;
  server_addr.sin_port        = htons(portnumber);
  /* Listen to all interfaces. */
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  /* Listen to an interface with a specific IP (requires <arpa/inet.h>). */
  /* inet_aton("127.0.0.1", &(server_addr.sin_addr)); */
  /* Zero the rest of the struct. */
  memset(&(server_addr.sin_zero), '\0', 8);
 
  /* Associate the socket with a port number using bind(). */
  if (bind(sfd, (struct sockaddr *)&server_addr, sizeof server_addr) < 0)
    {
      perror("bind");
      if (errno == EACCES)
        {
          /* Not running as root. */
          if (portnumber == portnumberdefault)
            {
              printf("Error: This server listens to port %d by default.\nYou must have root access to run servers which listen to port numbers below 1024.\n", portnumberdefault);
              printf("%s", usage);
            }
        }
      return 2;
    }
  
  /* Make this program a daemon using fork(). */
  switch (fork())
    {
    case -1:
      perror("fork");
      return 3;
      break;
    default:
      close(sfd);
      return 0;
      break;
    case 0:
      break;
    }
  
  addr_len = sizeof(struct sockaddr);
  
  /* Wait forever for new clients. */
  for (;;)
    {

      if ((numbytes = recvfrom(sfd, buf, MAXBUFLEN - 1 , 0, (struct sockaddr *)&client_addr, &addr_len)) < 0)
        {
          perror("recvfrom");
          exit(1);
        }

      if ((t = time(NULL)) < 0)
        {
          perror("daytimed-udp time");
          return 6;
        }
      
      /* Time message to be sent over the socket. */
      tm = localtime(&t);
      sprintf(timemsg, "%.4i-%.2i-%.2i %.2i:%.2i:%.2i %s\n", 
              tm->tm_year + 1900,
              tm->tm_mon + 1,
              tm->tm_mday,
              tm->tm_hour,
              tm->tm_min,
              tm->tm_sec,
              tm->tm_zone);

      /* Send the message to the client. */
      if ((numbytes = sendto(sfd, timemsg, strlen(timemsg), 0, (struct sockaddr *)&client_addr, addr_len)) < 0)
        {
          perror("daytimed-udp send");
          return 5;
        }
      
    }
}

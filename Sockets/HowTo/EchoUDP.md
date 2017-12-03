# Echo UDP

## Le serveur

```C
/* UDP echo server program -- echo-server-udp.c */

#include <stdio.h>      /* standard C i/o facilities */
#include <stdlib.h>     /* needed for atoi() */
#include <unistd.h>     /* defines STDIN_FILENO, system calls,etc */
#include <sys/types.h>  /* system data type definitions */
#include <sys/socket.h> /* socket specific definitions */
#include <netinet/in.h> /* INET constants and stuff */
#include <arpa/inet.h>  /* IP address conversion stuff */
#include <netdb.h>      /* gethostbyname */



/* this routine echos any messages (UDP datagrams) received */

#define MAXBUF 1024*1024

void echo( int sd ) {
    int len,n;
    char bufin[MAXBUF];
    struct sockaddr_in remote;

    /* need to know how big address struct is, len must be set before the
       call to recvfrom!!! */

    len = sizeof(remote);

    while (1) {
      /* read a datagram from the socket (put result in bufin) */
      n=recvfrom(sd,bufin,MAXBUF,0,(struct sockaddr *)&remote,&len);

      /* print out the address of the sender */
      printf("Got a datagram from %s port %d\n",
             inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));

      if (n<0) {
        perror("Error receiving data");
      } else {
        printf("GOT %d BYTES\n",n);
        /* Got something, just send it back */
        sendto(sd,bufin,n,0,(struct sockaddr *)&remote,len);
      }
    }
}

/* server main routine */

int main() {
  int ld;
  struct sockaddr_in skaddr;
  int length;

  /* create a socket
     IP protocol family (PF_INET)
     UDP protocol (SOCK_DGRAM)
  */

  if ((ld = socket( PF_INET, SOCK_DGRAM, 0 )) < 0) {
    printf("Problem creating socket\n");
    exit(1);
  }

  /* establish our address
     address family is AF_INET
     our IP address is INADDR_ANY (any of our IP addresses)
     the port number is assigned by the kernel
  */

  skaddr.sin_family = AF_INET;
  skaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  skaddr.sin_port = htons(0);

  if (bind(ld, (struct sockaddr *) &skaddr, sizeof(skaddr))<0) {
    printf("Problem binding\n");
    exit(0);
  }

  /* find out what port we were assigned and print it out */

  length = sizeof( skaddr );
  if (getsockname(ld, (struct sockaddr *) &skaddr, &length)<0) {
    printf("Error getsockname\n");
    exit(1);
  }

  /* port number's are network byte order, we have to convert to
     host byte order before printing !
  */
  printf("The server UDP port number is %d\n",ntohs(skaddr.sin_port));

  /* Go echo every datagram we get */
  echo(ld);
  return(0);
}
```

## Le client

```C
/* Simple UDP echo client - tries to send everything read from stdin
   as a single datagram (MAX 1MB)*/

#include <stdio.h>      /* standard C i/o facilities */
#include <stdlib.h>     /* needed for atoi() */
#include <unistd.h>     /* defines STDIN_FILENO, system calls,etc */
#include <sys/types.h>  /* system data type definitions */
#include <sys/socket.h> /* socket specific definitions */
#include <netinet/in.h> /* INET constants and stuff */
#include <arpa/inet.h>  /* IP address conversion stuff */
#include <netdb.h>      /* gethostbyname */
#include <string.h>

/* get_stdin reads from standard input until EOF is found,
   or the maximum bytes have been read.
*/

int get_stdin( char *buf, int maxlen ) {
  int i=0;
  int n;

  while ( (n=read(STDIN_FILENO,buf+i,maxlen-i)) > 0 ) {
    i+=n;
    if (i==maxlen) break;
  }

  if (n!=0) {
    perror("Error reading stdin");
    exit(1);
  }

  /* return the number of bytes read including the last read */
  return(i);
}


/* client program:

   The following must passed in on the command line:
      hostname of the server (argv[1])
      port number of the server (argv[2])
*/

#define MAXBUF 10*1024

int main( int argc, char **argv ) {
  int sk;
  struct sockaddr_in server;
  struct hostent *hp;
  char buf[MAXBUF];
  int buf_len;
  int n_sent;
  int n_read;


  /* Make sure we have the right number of command line args */

  if (argc!=3) {
    printf("Usage: %s <server name> <port number>\n",argv[0]);
    exit(0);
  }

  /* create a socket
     IP protocol family (PF_INET)
     UDP (SOCK_DGRAM)
  */

  if ((sk = socket( PF_INET, SOCK_DGRAM, 0 )) < 0)
    {
      printf("Problem creating socket\n");
      exit(1);
    }

  /* Using UDP we don't need to call bind unless we care what our
     port number is - most clients don't care */

  /* now create a sockaddr that will be used to contact the server

     fill in an address structure that will be used to specify
     the address of the server we want to connect to

     address family is IP  (AF_INET)

     server IP address is found by calling gethostbyname with the
     name of the server (entered on the command line)

     server port number is argv[2] (entered on the command line)
  */

  server.sin_family = AF_INET;
  if ((hp = gethostbyname(argv[1]))==0) {
    printf("Invalid or unknown host\n");
    exit(1);
  }

  /* copy the IP address into the sockaddr
     It is already in network byte order
  */

  memcpy( &server.sin_addr.s_addr, hp->h_addr, hp->h_length);

  /* establish the server port number - we must use network byte order! */
  server.sin_port = htons(atoi(argv[2]));

  /* read everything possible */
  buf_len = get_stdin(buf,MAXBUF);
  printf("Got %d bytes from stdin - sending...\n",buf_len);

  /* send it to the echo server */

  n_sent = sendto(sk,buf,buf_len,0,
                  (struct sockaddr*) &server,sizeof(server));

  if (n_sent<0) {
    perror("Problem sending data");
    exit(1);
  }

  if (n_sent!=buf_len) {
    printf("Sendto sent %d bytes\n",n_sent);
  }

  /* Wait for a reply (from anyone) */
  n_read = recvfrom(sk,buf,MAXBUF,0,NULL,NULL);
  if (n_read<0) {
    perror("Problem in recvfrom");
    exit(1);
  }

  printf("Got back %d bytes\n",n_read);
  /* send what we got back to stdout */
  if (write(STDOUT_FILENO,buf,n_read) < 0) {
    perror("Problem writing to stdout");
    exit(1);
  }
  return(0);
}
```
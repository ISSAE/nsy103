/* 
 * File:   wrsock.h
 * Author: pascalfares
 *
 * Created on 6 décembre 2014, 13:35
 * Updated 9 janvier 2017 : utilisation de getaddrinfo
 */

#ifndef WRSOCK_H
#define	WRSOCK_H

#include <sys/types.h> 
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int writes(int, char *, int);
int reads(int, char *, int);
struct addrinfo *getAddrInfo(const char *, const char *, int);
char* getNameInfo(struct sockaddr_in *sa);
struct sockaddr_in *creerSock(char *, char *, int, int *);
int bindedSocket(char *, char *, int, struct sockaddr_in *);
struct sockaddr_in *creerSockAddr(char *, char *, int);
#endif	/* WRSOCK_H */


/* 
 * File:   wrsock.h
 * Author: pascalfares
 *
 * Created on 6 décembre 2014, 13:35
 */

#ifndef WRSOCK_H
#define	WRSOCK_H

int writes(int, char *, int);
int reads(int, char *, int);
int bindedSocket(char *, int, int);
struct sockaddr_in *creerSockAddr(char *, int);
#endif	/* WRSOCK_H */


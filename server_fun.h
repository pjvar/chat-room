#ifndef _SERVER_INCLUDE_H_
#define _SERVER_INCLUDE_H_

#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include <sys/stat.h>
#include <fcntl.h>


int Socket(int,int,int);
int Bind(int,const struct sockaddr *,socklen_t);
int Listen(int,int);
int Accept(int,struct sockaddr *,socklen_t *);
int Connect(int,const struct sockaddr *,socklen_t);
int Open(const char *,int);

#endif

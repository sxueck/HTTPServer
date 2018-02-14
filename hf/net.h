/*
 * My Header File For Net Code
 * Create For SXueck
 */

#ifdef __net_h
#define __net_h
#endif

typedef unsigned char byte;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netdb.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdint.h>

#ifndef __MEMORY_H
#include <memory.h>
#endif

#ifndef __PTHREAD_H
#include <pthread.h>
#endif

#ifndef __IOSTREAM
#include <iostream>
#endif

#ifndef __STRING
#include <string>
#endif

//Error
#define IPADDRERR -14
#define BINDERR -15
#define ACCEPTERR -16
#define SENDERR -17
#define RECVERR -18
#define SOCKETERR -19
#define PORTERR -20

//Other
#define IPLEN 32

#ifndef __SOCKETS_HTTP_H__
#define __SOCKETS_HTTP_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 8080
#define BACKLOG 10

/*  server.c  */
int create_socket(void);
int bind_socket(int socket_fd);
int accept_and_receive(int socket_fd);

#endif /* __SOCKETS_H__ */

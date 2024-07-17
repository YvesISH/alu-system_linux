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
#define VERBOSE_ON 1
#define RESP_OK "HTTP/1.1 200 OK\r\n\r\n"
#define RESP_OK_LEN (sizeof(RESP_OK) - 1)

/**
 * init_socket - creates and binds a socket
 * Return: server file descriptor, or -1 on failure
 */
int init_socket(void)
{
    int serv_fd;
    struct sockaddr_in addr;

    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_fd == -1)
    {
        perror("socket");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(serv_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("bind");
        close(serv_fd);
        return -1;
    }

    if (listen(serv_fd, BACKLOG) == -1)
    {
        perror("listen");
        close(serv_fd);
        return -1;
    }

    return serv_fd;
}

/**
 * accept_recv - accepts a connection and receives a message
 * @serv_fd: server file descriptor
 * @buffer: buffer to store received message
 * @verbose: verbosity flag
 * Return: client file descriptor, or -1 on failure
 */
int accept_recv(int serv_fd, char *buffer, int verbose)
{
    int client_fd;
    ssize_t bytes_received;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    client_fd = accept(serv_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd == -1)
    {
        perror("accept");
        return -1;
    }

    bytes_received = recv(client_fd, buffer, BUFSIZ - 1, 0);
    if (bytes_received == -1)
    {
        perror("recv");
        close(client_fd);
        return -1;
    }

    buffer[bytes_received] = '\0'; /* Null-terminate the received message */

    if (verbose)
        printf("Received message:\n%s\n", buffer);

    return client_fd;
}

/**
 * print_body - print request path and all body key/value pairs
 * @buffer: HTTP request to print
 */
void print_body(char *buffer)
{
    char *saveptr, *token, *val;
    int i;

    strtok_r(buffer, " ", &saveptr);
    token = strtok_r(NULL, " ", &saveptr);
    printf("Path: %s\n", token);
    for (i = 0; i < 7; ++i)
        token = strtok_r(NULL, "\n", &saveptr);
    while (1)
    {
        token = strtok_r(NULL, "=", &saveptr);
        val = strtok_r(NULL, "&\"", &saveptr);
        if (val == NULL)
            break;
        printf("Body param: \"%s\" -> \"%s\"\n", token, val);
    }
}

/**
 * accept_connection - accept connections, print, and sends HTTP/1.1 request
 * @serv_fd: server file descriptor
 * Return: 0 on success, 1 on error
 */
int accept_connection(int serv_fd)
{
    int client_fd;
    char buffer[BUFSIZ];

    while (1)
    {
        client_fd = accept_recv(serv_fd, buffer, VERBOSE_ON);
        if (client_fd == -1)
            return (1);
        print_body(buffer);
        send(client_fd, RESP_OK, RESP_OK_LEN, 0);
        close(client_fd);
    }
    return (0);
}

/**
 * main - open IPv4 socket, listens, accepts, and prints recv message
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
    int serv_fd, ret;

    setbuf(stdout, NULL);
    serv_fd = init_socket();
    if (serv_fd == -1)
        return (1);
    ret = accept_connection(serv_fd);
    close(serv_fd);
    return (ret);
}


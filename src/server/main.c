
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "util.h"
#include "myirc.h"
#include "socket.h"
#include "socket_server.h"

static char usage(char *bin) {
    fprintf(stderr, "Usage: %s --help\n", bin);
    return 1;
}

void init_server_select(t_server_select *server_select, int server_fd) {
    server_select->timeout.tv_sec = 0;
    server_select->timeout.tv_usec = 5000;
    server_select->nfds = -1;
    server_select->readfds_n = 0;
    server_select->writefds_n = 0;
    FD_ZERO(&server_select->readfds);
    FD_ZERO(&server_select->writefds);
}

void add_readfd_server_select(t_server_select *server_select, int fd) {
    FD_SET(fd, &server_select->readfds);
    if (fd > server_select->nfds)
        server_select->nfds = fd + 1;
    server_select->readfds_n++;
}

char        init_irc_server(t_irc_server *irc_server) {
    if (!socket_init(&irc_server->fd_server))
        return 0;
    if (!socket_listen(&irc_server->fd_server,
                  irc_server->listen_address,
                  &irc_server->listen_port))
        return 0;
    irc_server->irc_clients = NULL;
    return 1;
}

int                 get_highest_read_fd(t_irc_server *irc_server) {
    int             fd;
    t_irc_client    *clients;

    clients = irc_server->irc_clients;
    fd = -1;
    while (clients) {
        if (clients->fd > fd)
            fd = clients->fd;
        clients = clients->next;
    }
    if (irc_server->fd_server > fd)
        fd = irc_server->fd_server;
    return fd;
}

int my_select(t_server_select *ss, t_irc_server *irc_server) {
    ss->nfds = get_highest_read_fd(irc_server) + 1;
    return select(ss->nfds, &ss->readfds,
                   &ss->writefds, &ss->exceptfds,
                   &ss->timeout);
}

void add_readfd_clients(t_server_select *server_select,
                        t_irc_client *clients) {
    while (clients) {
        if (clients->fd > server_select->nfds - 1)
            server_select->nfds = clients->fd + 1;
        FD_SET(clients->fd, &server_select->readfds);
        server_select->readfds_n++;
        clients = clients->next;
    }
}

void init_irc_client(t_irc_client *irc_client, int fd) {
    irc_client->fd = fd;
    irc_client->next = NULL;
}

void                new_irc_client(t_irc_server *irc_server, int fd_new_client) {
    t_irc_client    *irc_client;
    t_irc_client    *clients;

    irc_client = my_malloc(sizeof(t_irc_client));
    init_irc_client(irc_client, fd_new_client);
    clients = irc_server->irc_clients;
    if (!clients)
        irc_server->irc_clients = irc_client;
    else {
        while (clients->next)
            clients = clients->next;
        clients->next = irc_client;
    }
}

char    on_server_new_client(t_irc_server *irc_server) {
    int fd_new_client;

    if (!socket_accept(&irc_server->fd_server, &fd_new_client))
        return 0;
    new_irc_client(irc_server, fd_new_client);
    printf("New client !\n");
    return 1;
}

char                on_exit_client(t_irc_server *irc_server, t_irc_client *irc_client) {
    t_irc_client    *cur;
    t_irc_client    *prev;
    t_irc_client    *next;

    cur = irc_server->irc_clients;
    prev = NULL;
    while (cur) {
        next = cur->next;
        if (cur == irc_client) {
            if (prev)
                prev->next = cur->next;
            else
                irc_server->irc_clients = NULL;
            break;
        }
        prev = cur;
        cur = next;
    }
    socket_close(&irc_client->fd);
    free(irc_client);
    return 1;
}

char on_client_data(t_irc_server *irc_server, t_irc_client *irc_client) {
    memset(&irc_client->buffer, 0, BUFFER_SIZE);
    if (read(irc_client->fd, &irc_client->buffer, BUFFER_SIZE) <= 0) {
        on_exit_client(irc_server, irc_client);
        printf("client exit\n");
        return 0;
    }
    printf("new data!\n");
    return 1;
}

char                server_select_on_data(t_server_select *ss,
                              t_irc_server *irc_server) {
    t_irc_client    *client;
    t_irc_client    *next;

    if (FD_ISSET(irc_server->fd_server, &ss->readfds)) {
        if (!on_server_new_client(irc_server))
            return 0;
    }
    client = irc_server->irc_clients;
    while (client) {
        next = client->next;
        if (FD_ISSET(client->fd, &ss->readfds)) {
            on_client_data(irc_server, client);
        }
        client = next;
    }
    return 1;
}

char                start_irc_server(t_irc_server *irc_server) {
    t_server_select ss;
    int             retrv;

    if (!init_irc_server(irc_server))
        return 0;
    while (1) {
        init_server_select(&ss, irc_server->fd_server);
        add_readfd_server_select(&ss, irc_server->fd_server);
        add_readfd_clients(&ss, irc_server->irc_clients);
        retrv = my_select(&ss, irc_server);
        if (retrv == 0) {}
        else if (retrv == -1)
            EXIT_ERROR(0, "select error : %s\n", strerror(errno))
        else if (!server_select_on_data(&ss, irc_server))
            return 0;
    }
    socket_close(&irc_server->fd_server);
    return 1;
}

int                 main(int ac, char **av) {
    t_irc_server    irc_server;

    if (ac != 2 || !is_number(av[1]))
        return usage(av[0]);
    irc_server.listen_address = LISTEN_ADDRESS;
    irc_server.listen_port = atoi(av[1]);
    irc_server.irc_clients = NULL;
    return !start_irc_server(&irc_server);
}
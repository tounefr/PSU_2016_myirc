
#include "myirc.h"

static void init_server_select(t_server_select *server_select,
                        int server_fd)
{
    server_select->timeout.tv_sec = 0;
    server_select->timeout.tv_usec = 5000;
    server_select->nfds = -1;
    server_select->readfds_n = 0;
    server_select->writefds_n = 0;
    FD_ZERO(&server_select->readfds);
    FD_ZERO(&server_select->writefds);
}

static void add_readfd_server_select(t_server_select *server_select,
                              int fd)
{
    FD_SET(fd, &server_select->readfds);
    if (fd > server_select->nfds)
        server_select->nfds = fd + 1;
    server_select->readfds_n++;
}

static int                 get_highest_read_fd(t_irc_server *irc_server)
{
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

static void add_readfd_clients(t_server_select *server_select,
                        t_irc_client *clients)
{
    while (clients) {
        if (clients->fd > server_select->nfds - 1)
            server_select->nfds = clients->fd + 1;
        FD_SET(clients->fd, &server_select->readfds);
        server_select->readfds_n++;
        clients = clients->next;
    }
}

int my_select(t_server_select *ss, t_irc_server *irc_server)
{
    init_server_select(ss, irc_server->fd_server);
    add_readfd_server_select(ss, irc_server->fd_server);
    add_readfd_clients(ss, irc_server->irc_clients);
    ss->nfds = get_highest_read_fd(irc_server) + 1;
    return select(ss->nfds, &ss->readfds,
                  &ss->writefds, &ss->exceptfds,
                  &ss->timeout);
}


/*
** my_select.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:17:08 2017 Thomas HENON
** Last update Sat May 27 20:17:09 2017 Thomas HENON
*/

#include "server.h"

static int
get_highest_read_fd(t_irc_server *irc_server)
{
    int fd;
    t_clients_list *clients;
    t_client *client;

    clients = irc_server->irc_clients;
    fd = -1;
    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
        if (client->fd > fd)
            fd = client->fd;
    }
    if (irc_server->fd_server > fd)
        fd = irc_server->fd_server;
    return fd;
}

static void
add_readfd_clients(t_my_select *server_select,
                   t_clients_list *clients)
{
    t_client *client;

    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
        if (client->fd > server_select->nfds - 1)
            server_select->nfds = client->fd + 1;
        FD_SET(client->fd, &server_select->readfds);
        server_select->readfds_n++;
    }
}

int
my_select(t_my_select *ss,
          t_irc_server *irc_server)
{
    init_my_select(ss);
    add_readfd_my_select(ss, irc_server->fd_server);
    add_readfd_clients(ss, irc_server->irc_clients);
    ss->nfds = get_highest_read_fd(irc_server) + 1;
    return select(ss->nfds, &ss->readfds,
                  &ss->writefds, &ss->exceptfds,
                  &ss->timeout);
}


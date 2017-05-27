
#include "myirc.h"

void    init_irc_client(t_irc_client *irc_client, int fd)
{
    irc_client->fd = fd;
    irc_client->next = NULL;
    irc_client->cbuffer = cbuffer_new(IRC_PACKET_SIZE);
    irc_client->registred_channels = NULL;
}

void                new_irc_client(t_irc_server *irc_server,
                                   int fd_new_client)
{
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


/*
** client.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:18:00 2017 Thomas HENON
** Last update Sat May 27 20:18:01 2017 Thomas HENON
*/

#include "myirc.h"

void    init_irc_client(t_irc_client *irc_client, int fd)
{
    irc_client->fd = fd;
    irc_client->next = NULL;
    irc_client->cbuffer = cbuffer_new(IRC_PACKET_SIZE);
    irc_client->registred_channels = NULL;
    irc_client->pseudo = NULL;
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

char
check_pseudo_already_used(t_irc_server *irc_server,
                          char *pseudo)
{
    t_irc_client    *clients;

    clients = irc_server->irc_clients;
    while (clients) {
        if (clients->pseudo && !strcmp(clients->pseudo, pseudo))
            return 1;
        clients = clients->next;
    }
    return 0;
}

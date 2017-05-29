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

void
init_irc_client(t_irc_client *irc_client,
                int fd)
{
    irc_client->fd = fd;
    irc_client->cbuffer = cbuffer_new(IRC_PACKET_SIZE);
    irc_client->registred_channels = NULL;
    irc_client->pseudo = NULL;
    irc_client->realname = NULL;
}

void
new_irc_client(t_irc_server *irc_server,
               int fd_new_client)
{
    t_irc_client *irc_client;
    t_clients_list *clients;

    irc_client = my_malloc(sizeof(t_irc_client));
    init_irc_client(irc_client, fd_new_client);
    generic_list_append(&irc_server->irc_clients, (void*)irc_client);
}

char
check_pseudo_already_used(t_irc_server *irc_server,
                          char *pseudo)
{
    t_clients_list *clients;
    t_irc_client *client;

    clients = irc_server->irc_clients;
    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
        if (client->pseudo && !strcmp(client->pseudo, pseudo))
            return 1;
    }
    return 0;
}

/*
** client.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:18:00 2017 Thomas HENON
** Last update Sat May 27 20:18:01 2017 Thomas HENON
*/

#include "server.h"

void
init_client(t_client *irc_client,
                int fd)
{
    irc_client->pseudo = NULL;
    irc_client->user = NULL;
    irc_client->realname = NULL;
    irc_client->fd = fd;
    irc_client->logged = 0;
    irc_client->cbuffer = cbuffer_new(IRC_PACKET_SIZE);
    irc_client->registred_channels = NULL;
    socket_infos(&fd, &irc_client->socket_infos);
}

void
new_irc_client(t_irc_server *irc_server,
               int fd_new_client)
{
    t_client *irc_client;

    irc_client = my_malloc(sizeof(t_client));
    init_client(irc_client, fd_new_client);
    generic_list_append(&irc_server->irc_clients, irc_client);
}

char
free_irc_client(void *data)
{
    t_client *irc_client;

    irc_client = (t_client*)data;
    if (!irc_client)
        return 0;
    if (irc_client->pseudo)
        free(irc_client->pseudo);
    if (irc_client->user)
        free(irc_client->user);
    if (irc_client->realname)
        free(irc_client->realname);
    if (irc_client->cbuffer)
        cbuffer_free(irc_client->cbuffer);
    free_socket_infos(&irc_client->socket_infos);
//    free(irc_client);
    return 1;
}

char
check_pseudo_already_used(t_irc_server *irc_server,
                          char *pseudo)
{
    t_clients_list *clients;
    t_client *client;

    clients = irc_server->irc_clients;
    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
        if (client->pseudo && !strcmp(client->pseudo, pseudo))
            return 1;
    }
    return 0;
}

char
on_exit_client(t_irc_server *irc_server,
               t_client *irc_client)
{
    t_channels_list *channels_list;
    t_channel *channel;

    channels_list = irc_client->registred_channels;
    while ((channel = generic_list_foreach(channels_list))) {
        channels_list = NULL;
        announce_channel_client_part(irc_client, channel);
        generic_list_remove(&channel->clients, irc_client, NULL);
    }
    socket_close(&irc_client->fd);
    generic_list_remove(&irc_server->irc_clients, irc_client, NULL);//TODO: fix NULL
    return 1;
}
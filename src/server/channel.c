/*
** channel.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 12:37:41 2017 Thomas HENON
** Last update Sun May 28 12:37:41 2017 Thomas HENON
*/

#include <stdlib.h>
#include "myirc.h"
#include "util.h"

static void
append_channel_in_list(t_irc_server *irc_server,
                       t_irc_channel *irc_channel)
{
    t_irc_channel *channels;

    channels = irc_server->channels;
    if (!channels) {
        irc_server->channels = irc_channel;
    } else {
        while (channels->next)
            channels = channels->next;
        channels->next = irc_channel;
    }
}

t_irc_channel*
new_irc_channel(t_irc_server *irc_server, char *name)
{
    t_irc_channel *irc_channel;

    irc_channel = my_malloc(sizeof(t_irc_channel));
    if (!(irc_channel->name = strdup(name)))
        malloc_error();
    irc_channel->max_clients = IRC_CHANNEL_MAX_CLIENTS;
    irc_channel->clients = NULL;
    irc_channel->op = NULL;
    irc_channel->next = NULL;
    append_channel_in_list(irc_server, irc_channel);
    return irc_channel;
}

t_irc_channel*
irc_channel_exists(t_irc_server *irc_server, char *name)
{
    t_irc_channel *channels;

    channels = irc_server->channels;
    while (channels) {
        if (channels->name && !strcmp(channels->name, name))
            return channels;
        channels = channels->next;
    }
    return NULL;
}

char
client_join_channel(t_irc_client *client, t_irc_channel *channel)
{
    t_irc_client *clients;

    clients = channel->clients;
    if (!clients) {

    } else {
        while (clients->next)
            clients = clients->next;
        clients->next = client;
    }
}

char
client_is_in_channel(t_irc_channel *channel, t_irc_client *client)
{
    t_irc_client *clients;

    clients = channel->clients;
    while (clients) {
        if (clients == client)
            return 1;
        clients = clients->next;
    }
    return 0;
}

char
client_leave_channel(t_irc_client *client, t_irc_channel *channel)
{

}

void
free_irc_channel(t_irc_channel *irc_channel)
{
    if (irc_channel->name)
        free(irc_channel->name);
    free(irc_channel);
}

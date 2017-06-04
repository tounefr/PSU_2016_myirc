/*
** channel.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 12:37:41 2017 Thomas HENON
** Last update Sun May 28 12:37:41 2017 Thomas HENON
*/

#include "server.h"

t_channel*
new_irc_channel(t_channels_list **channels, char *name)
{
    t_channel *irc_channel;

    irc_channel = my_malloc(sizeof(t_channel));
    irc_channel->name = my_strdup(name);
    irc_channel->max_clients = IRC_CHANNEL_MAX_CLIENTS;
    irc_channel->clients = NULL;
    irc_channel->op = NULL;
    irc_channel->topic = my_strdup("Mon super topic");
    generic_list_append(channels, irc_channel);
    return irc_channel;
}

t_channel*
irc_channel_exists(t_channels_list *channels, char *name)
{
    t_channel *channel;

    while ((channel = generic_list_foreach(channels))) {
        channels = NULL;
        if (channel->name && !strcmp(channel->name, name))
            return channel;
    }
    return NULL;
}

char
client_is_in_channel(t_channel *channel, t_client *to_find)
{
    t_client *client;
    t_clients_list *clients;

    clients = channel->clients;
    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
        if (client == to_find)
            return 1;
    }
    return 0;
}
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

t_irc_channel*
new_irc_channel(t_irc_server *irc_server, char *name)
{
    t_irc_channel *irc_channel;

    irc_channel = my_malloc(sizeof(t_irc_channel));
    irc_channel->name = my_strdup(name);
    irc_channel->max_clients = IRC_CHANNEL_MAX_CLIENTS;
    irc_channel->clients = NULL;
    irc_channel->op = NULL;
    irc_channel->topic = my_strdup("Mon super topic");
    generic_list_append(&irc_server->channels, irc_channel);
    return irc_channel;
}

char*
normalize_channel_name(char *channel)
{
    int i;

    if (!channel)
        return NULL;
    if (channel[0] == '&' || channel[0] == '#')
        channel++;
    if (strlen(channel) > 200)
        EXIT_ERROR(NULL, "channel name > 200\n")
    i = -1;
    while (channel[++i]) {
        if (channel[i] == 7 || channel[i] == ' ')
            EXIT_ERROR(NULL, "wrong channel name\n")
    }
    channel = my_strdup(channel);
    return channel;
}

t_irc_channel*
irc_channel_exists(t_irc_server *irc_server, char *name)
{
    t_channels_list *channels;
    t_irc_channel *channel;

    if (!name)
        return NULL;
    channels = irc_server->channels;
    while ((channel = generic_list_foreach(channels))) {
        channels = NULL;
        if (channel->name && !strcmp(channel->name, name))
            return channel;
    }
    return NULL;
}

char
client_is_in_channel(t_irc_channel *channel, t_irc_client *to_find)
{
    t_irc_client *client;
    t_clients_list *clients;

    clients = channel->clients;
    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
        if (client == to_find)
            return 1;
    }
    return 0;
}
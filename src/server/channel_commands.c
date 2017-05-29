/*
** channel_commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:06:38 2017 Thomas HENON
** Last update Sun May 28 00:06:39 2017 Thomas HENON
*/

#include <stdlib.h>
#include <string.h>
#include "myirc.h"

char
send_client_list_on_channel(t_irc_server *irc_server,
                            t_irc_channel *channel)
{
    t_clients_list  *clients;
    t_irc_client    *client;

    clients = channel->clients;
    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
        dprintf(client->fd, "352 %s %s %s %s %s %s %s %s\r\n",
                channel->name, client->pseudo,
                "<host>", "<server>", "<nick>",
                "<H|G>[*][@|+]", ":<hopcount>", "<real name>");
    }
}

char
on_join_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    t_packet *res;
    char *channels_names;
    char *channel_name;
    t_irc_channel *channel;

    if (packet->nbr_params == 0)
        return dprintf(irc_client->fd, "461 :Not enough parameters\r\n");
    channels_names = my_strdup(packet->params[0]);
    while ((channel_name = strtok(channels_names, " "))) {
        channels_names = NULL;
        if (!(channel = irc_channel_exists(irc_server, channel_name)))
            channel = new_irc_channel(irc_server, channel_name);
        if (client_is_in_channel(channel, irc_client))
            break;
        generic_list_append(&channel->clients, irc_client);
        dprintf(irc_client->fd, "332 %s %s :%s\r\n",
                irc_client->pseudo, channel->name, channel->topic);
        send_client_list_on_channel(irc_server, channel);
    }
    free(channels_names);
    return 1;
}

char msg_channel(t_irc_server *irc_server,
                           t_irc_client *irc_client,
                           t_packet *packet,
                           char *channel_name)
{
    t_irc_channel *channel;
    t_clients_list *clients;
    t_irc_client *client;

    if (!(channel_name = normalize_channel_name(packet->params[0])))
        return 1;
    if (!(channel = irc_channel_exists(irc_server, channel_name)))
        return 1;
    if (!client_is_in_channel(channel, irc_client))
        return 1;
    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
//        dprintf(client->fd, )
    }
}

char
on_privmsg_command(t_irc_server *irc_server,
                   t_irc_client *irc_client,
                   t_packet *packet)
{
    char *channel_name;

    if (packet->nbr_params != 1)
        return 1;
    if (packet->params[0][0] == '#')
        return msg_channel(irc_server, irc_client, packet, channel_name);

    return 1;
}

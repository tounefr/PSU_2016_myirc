/*
** commands2.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc/src/server
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu Jun  8 18:09:40 2017 Thomas HENON
** Last update Thu Jun  8 18:09:40 2017 Thomas HENON
*/

#include "server.h"

char
on_list_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet)
{
    t_channels_list *channels;
    t_channel *channel;
    char *channel_to_find;

    channel_to_find = NULL;
    if (packet->nbr_params >= 1) {
        channel_to_find = packet->params[0];
        if (!(channel_to_find = normalize_channel_name(channel_to_find)))
            return 1;
    }
    channels = irc_server->channels;
    dprintf(irc_client->fd, ":%s 321 %s Channel :Users Name\r\n",
            IRC_SERVER_HOST, irc_client->pseudo);
    while ((channel = generic_list_foreach(channels))) {
        channels = NULL;
        if (!channel_to_find || strstr(channel->name, channel_to_find)) {
            dprintf(irc_client->fd, ":%s 322 %s #%s :%s\r\n",
                    IRC_SERVER_HOST, irc_client->pseudo,
                    channel->name, channel->topic);
        }
    }
    return dprintf(irc_client->fd, ":%s 323 %s :End of /LIST\r\n",
            IRC_SERVER_HOST, irc_client->pseudo);
}

char
announce_channel_client_part(t_client *irc_client,
                             t_channel *irc_channel)
{
    t_clients_list *clients_in_channel;
    t_client *client_in_channel;

    clients_in_channel = irc_channel->clients;
    while ((client_in_channel = generic_list_foreach(clients_in_channel))) {
        clients_in_channel = NULL;
        dprintf(client_in_channel->fd, ":%s!~%s@127.0.0.1 PART #%s\r\n",
                irc_client->pseudo, irc_client->pseudo, irc_channel->name);
    }
    return 1;
}

char
on_part_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet)
{
    t_channels_list *channels;
    t_channel *channel;
    char *channel_name;

    if (packet->nbr_params == 0)
        return dprintf(irc_client->fd, "461 PART :Not enough parameters\r\n");
    if (!(channel_name = normalize_channel_name(packet->params[0])))
        return dprintf(irc_client->fd, "403 %s :No such channel\r\n",
                       packet->params[0]);
    channels = irc_client->registred_channels;
    while ((channel = generic_list_foreach(channels))) {
        channels = NULL;
        if (!strcmp(channel_name, channel->name)) {
            announce_channel_client_part(irc_client, channel);
            generic_list_remove(&channel->clients,
                                irc_client, NULL);
            generic_list_remove(&irc_client->registred_channels,
                                channel, NULL);
            if (generic_list_count(channel->clients) == 0)
                generic_list_remove(&irc_server->channels, channel,
                                    free_channel);
            return 1;
        }
    }
    return 1;
}

char
on_who_command(t_irc_server *irc_server,
               t_client *irc_client,
               t_packet *packet)
{
    (void)irc_server;
    (void)irc_client;
    (void)packet;
    return 1;
}

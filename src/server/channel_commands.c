/*
** channel_commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:06:38 2017 Thomas HENON
** Last update Sun May 28 00:06:39 2017 Thomas HENON
*/

#include "server.h"

char
send_channel_client_list(t_irc_server *irc_server,
                         t_client *irc_client,
                         t_channel *irc_channel)
{
    t_clients_list *clients_in_channel;
    t_client *client_in_channel;
    char pseudos_buffer[512];
    int i;
    int i2;

    clients_in_channel = irc_channel->clients;
    do {
        i = -1;
        i2 = 0;
        memset(pseudos_buffer, 0, sizeof(pseudos_buffer));
        while ((client_in_channel = generic_list_foreach(clients_in_channel))
               && ++i < 10) {
            clients_in_channel = NULL;
            if (i > 0)
                i2 += sprintf(&pseudos_buffer[i2], " ");
            i2 += sprintf(&pseudos_buffer[i2], "%s", client_in_channel->pseudo);
        }
        dprintf(irc_client->fd, ":%s 353 %s @ #%s :%s\r\n",
                IRC_SERVER_HOST, irc_client->pseudo,
                irc_channel->name, pseudos_buffer);
    } while (client_in_channel);
    dprintf(irc_client->fd, ":%s 366 %s #%s :End of /NAMES list.\r\n",
            IRC_SERVER_HOST, irc_client->pseudo, irc_channel->name);
}

char
announce_client_joined(t_channel *irc_channel,
                       t_client *irc_client)
{
    t_clients_list *clients_in_channel;
    t_client *client_in_channel;

    clients_in_channel = irc_channel->clients;
    while ((client_in_channel = generic_list_foreach(clients_in_channel))) {
        clients_in_channel = NULL;
        if (irc_client == client_in_channel)
            continue;
        dprintf(client_in_channel->fd, ":%s JOIN #%s\r\n",
                irc_client->pseudo, irc_channel->name);
    }
}

char
on_join_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet)
{
    t_packet *res;
    char *channel_name;
    t_channel *channel;

    if (packet->nbr_params == 0)
        return dprintf(irc_client->fd, "461 :Not enough parameters\r\n");
    if (!irc_client->pseudo)
        return 1;
    channel_name = packet->params[0];
    if (!(channel_name = normalize_channel_name(channel_name)))
        return 1;
    if (!(channel = irc_channel_exists(irc_server->channels, channel_name)))
        channel = new_irc_channel(&irc_server->channels, channel_name);
    if (client_is_in_channel(channel, irc_client))
        return 1;
    generic_list_append(&channel->clients, irc_client);
    generic_list_append(&irc_client->registred_channels, channel);
    dprintf(irc_client->fd, ":%s!~%s@127.0.0.1 JOIN #%s\r\n",
            irc_client->pseudo, irc_client->user, channel_name);
    dprintf(irc_client->fd, ":%s 331 %s #%s :No topic is set\r\n",
            IRC_SERVER_HOST, irc_client->pseudo, channel_name);
    dprintf(irc_client->fd, ":%s MODE #%s +ns\r\n",
            IRC_SERVER_HOST, channel_name);
    send_channel_client_list(irc_server,irc_client, channel);
    announce_client_joined(channel, irc_client);
    return 1;
}

char
send_msg_channel(t_irc_server *irc_server,
                 t_client *irc_client,
                 t_packet *packet,
                 char *channel_name)
{
    t_channel *channel;
    t_clients_list *clients;
    t_client *client;

    if (!(channel_name = normalize_channel_name(packet->params[0])))
        return exit_error(1, "error : normalize_channel_name\n");
    if (!(channel = irc_channel_exists(irc_server->channels, channel_name)))
        return exit_error(1, "error : irc_channel_exists\n");
    if (!client_is_in_channel(channel, irc_client))
        return exit_error(1, "error : client_is_in_channel\n");
    clients = channel->clients;
    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
        /*if (irc_client == client)
            continue;*/
        dprintf(client->fd, ":%s PRIVMSG #%s :%s\r\n",
                irc_client->pseudo, channel->name, packet->content);
    }
}

char
send_msg_user(t_irc_server *irc_server,
              t_client *irc_client,
              t_packet *packet)
{
    t_clients_list *clients_list;
    t_client *client;

    clients_list = irc_server->irc_clients;
    while ((client = generic_list_foreach(clients_list))) {
        clients_list = NULL;
        if (!strcmp(client->pseudo, packet->params[0])) {
            return dprintf(client->fd, ":%s PRIVMSG %s :%s\r\n",
                           irc_client->pseudo, client->pseudo,
                           packet->content);
        }
    }
}

char
on_privmsg_command(t_irc_server *irc_server,
                   t_client *irc_client,
                   t_packet *packet)
{
    char *channel_name;

    if (packet->nbr_params != 1)
        return 1;
    if (packet->params[0][0] == '#')
        return send_msg_channel(irc_server, irc_client,
                                packet, channel_name);
    else
        return send_msg_user(irc_server, irc_client, packet);
    return 1;
}

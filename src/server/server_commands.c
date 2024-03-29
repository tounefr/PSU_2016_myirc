/*
** server_commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:06:26 2017 Thomas HENON
** Last update Sun May 28 00:06:26 2017 Thomas HENON
*/

#include "server.h"

char
announce_nick_changed(t_client *irc_client,
                      t_packet *packet)
{
    t_channels_list *registred_channels;
    t_channel *irc_channel;
    t_clients_list *clients_in_channel;
    t_client *client_in_channel;

    registred_channels = irc_client->registred_channels;
    while ((irc_channel = generic_list_foreach(registred_channels))) {
        registred_channels = NULL;
        clients_in_channel = irc_channel->clients;
        while ((client_in_channel = generic_list_foreach(clients_in_channel))) {
            clients_in_channel = NULL;
            if (client_in_channel == irc_client)
                continue;
            dprintf(client_in_channel->fd, ":%s NICK :%s\r\n",
                    irc_client->pseudo, packet->params[0]);
        }
    }
    return 1;
}

char
on_nick_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet)
{
    if (packet->nbr_params == 0)
        return dprintf(irc_client->fd, ":%s 431 :No nickname given\r\n",
                       IRC_SERVER_HOST);
    if (check_pseudo_already_used(irc_server, packet->params[0]))
        return dprintf(irc_client->fd,
                       "433 %s %s :Nickname is already in use\r\n",
                       irc_client->pseudo, packet->params[0]);
    dprintf(irc_client->fd, ":%s NICK :%s\r\n",
            (irc_client->pseudo ? irc_client->pseudo : IRC_SERVER_HOST),
            packet->params[0]);
    announce_nick_changed(irc_client, packet);
    if (irc_client->pseudo)
        free(irc_client->pseudo);
    irc_client->pseudo = my_strdup(packet->params[0]);
    return 1;
}

char
on_names_command(t_irc_server *irc_server,
                 t_client *irc_client,
                 t_packet *packet)
{
    t_channels_list *channels;
    t_channel *channel;
    char *channel_name;

    if (!(channel_name = packet->params[0]))
        return 0;
    if (!(channel_name = normalize_channel_name(channel_name)))
        return 0;
    channels = irc_server->channels;
    if (!(channel = irc_channel_exists(channels, channel_name)))
        return dprintf(irc_client->fd, ":%s 401 %s #%s"
                               " :No such nick/channel\r\n",
                       IRC_SERVER_HOST, irc_client->pseudo, channel_name);
    send_channel_client_list(irc_server, irc_client, channel);
    return 1;
}

char
on_user_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet)
{
    (void)irc_server;
    if (packet->nbr_params < 3)
        return dprintf(irc_client->fd, ":%s 461 :Not enough parameters\r\n",
                       IRC_SERVER_HOST);
    irc_client->user = my_strdup(packet->params[0]);
    irc_client->realname = my_strdup(packet->content);
    if (irc_client->pseudo)
        irc_client->logged = 1;
    dprintf(irc_client->fd, ":%s 001 %s :Welcome\r\n",
            IRC_SERVER_HOST, irc_client->pseudo);
    dprintf(irc_client->fd, ":%s 376 %s :End of /MOTD command\r\n",
            IRC_SERVER_HOST, irc_client->pseudo);
    return 1;
}

char
on_quit_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet)
{
    (void)irc_server;
    (void)packet;
    on_exit_client(irc_server, irc_client);
    return 1;
}

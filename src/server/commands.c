/*
** commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:18:06 2017 Thomas HENON
** Last update Sat May 27 20:18:06 2017 Thomas HENON
*/

#include <stdlib.h>
#include "myirc.h"

t_command_callback commands_callbacks[N_COMMAND_CALLBACK] =
{
        { "JOIN", on_join_command },
        { "LIST", on_list_command },
        { "NICK", on_nick_command },
        { "PART", on_part_command },
        { "WHO", on_who_command },
        { "NAMES", on_names_command },
        { "PRIVMSG", on_privmsg_command },
        { "USER", on_user_command },
        { "QUIT", on_quit_command },
        { "MODE", on_mode_command },
        { "PING", on_ping_command }
};

char
on_ping_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    dprintf(irc_client->fd, "PONG %s\r\n", packet->params[0]);
    return 1;
}


char
on_mode_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    //dprintf(irc_client->fd, "324 thomas #test +Pgmnstzj 2:2\r\n");
    return 1;
}

char
on_list_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    return 1;
}

char
announce_channel_client_part(t_irc_client *irc_client,
                             t_irc_channel *irc_channel)
{
    t_clients_list *clients_in_channel;
    t_irc_client *client_in_channel;

    clients_in_channel = irc_channel->clients;
    while ((client_in_channel = generic_list_foreach(clients_in_channel))) {
        clients_in_channel = NULL;
        //thomas__!~thomas@163.5.141.79 PART #test
        dprintf(client_in_channel->fd, ":%s!~%s@127.0.0.1 PART #%s\r\n",
                irc_client->pseudo, irc_client->user, irc_channel->name);
    }
}

char
on_part_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    t_channels_list *channels;
    t_irc_channel *channel;
    char *channel_name;

    if (packet->nbr_params == 0)
        return dprintf(irc_client->fd, "461 PART :Not enough parameters\r\n");
    if (!(channel_name = normalize_channel_name(packet->params[0])))
        return dprintf(irc_client->fd, "403 %s :No such channel\r\n", packet->params[0]);
    channels = irc_client->registred_channels;
    while ((channel = generic_list_foreach(channels))) {
        channels = NULL;
        if (!strcmp(channel_name, channel->name)) {
            announce_channel_client_part(irc_client, channel);
            generic_list_remove(&irc_client->registred_channels,
                                channel, free_irc_channel);
            return 1;

        }
    }
    return 1;
}

char
on_who_command(t_irc_server *irc_server,
               t_irc_client *irc_client,
               t_packet *packet)
{
    dprintf(irc_client->fd, "352 thomas #test ~thomas 163.5.141.79 cherryh.freenode.net thomas H+ :0 thomas\r\n");
    dprintf(irc_client->fd, "315 thomas #test :End of /WHO list\r\n");
    return 1;
}
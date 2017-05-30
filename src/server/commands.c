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
        { "JOIN", simple_space_parser, on_join_command }, // /join   1
        { "LIST", simple_space_parser, on_list_command }, // /list  0, 1, 2
        { "NICK", simple_space_parser, on_nick_command }, // /nick 0, 1
        { "PART", simple_space_parser, on_part_command }, // /part 1
        { "WHO", simple_space_parser, on_who_command }, // /users    0, 1
        { "NAMES", simple_space_parser, on_names_command }, // /names   0, 1
        { "PRIVMSG", simple_space_parser, on_privmsg_command }, // /msg ou $msg     1
        { "USER", simple_space_parser, on_user_command },
        { "QUIT", simple_space_parser, on_quit_command },
        { "MODE", simple_space_parser, on_mode_command },
        { "PING", simple_space_parser, on_ping_command }
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
            generic_list_remove(&irc_client->registred_channels, channel);
            generic_list_remove(&channel->clients, irc_client);

            /*if (generic_list_count(channel->clients) == 0)
                free_irc_channel(irc_server, channel);*/

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
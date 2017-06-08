/*
** commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:18:06 2017 Thomas HENON
** Last update Sat May 27 20:18:06 2017 Thomas HENON
*/

#include "server.h"

t_command_callback commands_callbacks[N_COMMAND_CALLBACK] =
{
    { "JOIN", on_join_command, FLAG_LOG_FIRST },
    { "LIST", on_list_command, FLAG_LOG_FIRST },
    { "NICK", on_nick_command, FLAG_NONE },
    { "PART", on_part_command, FLAG_LOG_FIRST },
    { "WHO", on_who_command, FLAG_LOG_FIRST },
    { "NAMES", on_names_command, FLAG_LOG_FIRST },
    { "PRIVMSG", on_privmsg_command, FLAG_LOG_FIRST },
    { "USER", on_user_command, FLAG_NONE },
    { "QUIT", on_quit_command, FLAG_NONE },
    { "MODE", on_mode_command, FLAG_LOG_FIRST },
    { "PING", on_ping_command, FLAG_NONE },
    { "WHOIS", on_whois_command, FLAG_LOG_FIRST }
};

char
client_whois(t_irc_server *irc_server,
             t_client *irc_client,
             t_packet *packet)
{
    t_clients_list *clients;

}

char
channel_whois(t_irc_server *irc_server,
              t_client *irc_client,
              t_packet *packet)
{

}

char
on_whois_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet)
{

    return 1;
}

char
on_ping_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet)
{
    dprintf(irc_client->fd, "PONG %s\r\n", packet->params[0]);
    return 1;
}

char
on_mode_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet)
{
    char *channel_name;
    t_channels_list *channels;
    t_channel *channel;

    return 1;
    if (packet->nbr_params == 0)
        return 1;
    if (packet->params[0][0] == '#') {
        if (!(channel_name = normalize_channel_name(packet->params[0])))
            return 1;
        if (!(channel = irc_channel_exists(irc_server->channels, channel_name)))
            return 1;
        dprintf(irc_client->fd, "324 %s #%s +ns\r\n", irc_client->pseudo, channel->name);
        return 1;
    }
    return 1;
}
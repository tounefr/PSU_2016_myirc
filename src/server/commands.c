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
    //:verne.freenode.net 324 Guest13741 #test +Pgmnstzj 2:2
    //dprintf(irc_client->fd, "324 thomas #test +Pgmnstzj 2:2\r\n");
    return 1;
}

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
            IRC_SERVER_HOST,
            irc_client->pseudo);
    while ((channel = generic_list_foreach(channels))) {
        channels = NULL;
        if (!channel_to_find || strstr(channel->name, channel_to_find)) {
            dprintf(irc_client->fd, "322 %s #%s 4 :%s\r\n",
                    irc_client->pseudo, channel->name, channel->topic);
        }
    }
    dprintf(irc_client->fd, ":%s 323 %s :End of /LIST\r\n",
            IRC_SERVER_HOST, irc_client->pseudo);
    return 1;
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
        //thomas__!~thomas@163.5.141.79 PART #test
        //:thomas!~thomas@163.5.141.79 PART #test
        dprintf(client_in_channel->fd, ":%s!~%s@127.0.0.1 PART #%s\r\n",
                irc_client->pseudo, irc_client->pseudo, irc_channel->name);
    }
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
                generic_list_remove(&irc_server->channels, channel, free_channel);
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
    dprintf(irc_client->fd, "352 thomas #test ~thomas 163.5.141.79 cherryh.freenode.net thomas H+ :0 thomas\r\n");
    dprintf(irc_client->fd, "315 thomas #test :End of /WHO list\r\n");
    return 1;
}
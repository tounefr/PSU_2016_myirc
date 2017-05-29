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
send_RPL_TOPIC(t_irc_client *irc_client,
               t_irc_channel *channel)
{
    t_packet *res;

    res = init_packet(NULL);
    packet_set_params(res, 2, irc_client->pseudo, channel->name);
    packet_set(res, "332", channel->topic);
    return send_reply_packet(irc_client->fd, res);
}

char
send_ERR_NEEDMOREPARAMS(t_irc_client *irc_client)
{
    t_packet *res;

    res = init_packet(NULL);
    packet_set(res, "461", "Not enough parameters");
    send_reply_packet(irc_client->fd, res);
}

char
on_join_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    t_packet *res;

    if (packet->nbr_params == 0)
        return send_ERR_NEEDMOREPARAMS(irc_client);

    char *channels_names;
    char *channel_name;
    t_irc_channel *channel;

    channels_names = my_strdup(packet->params[0]);
    while ((channel_name = strtok(channels_names, " "))) {
        channels_names = NULL;
        if (!(channel = irc_channel_exists(irc_server, channel_name))) {
            printf("channel doesn't exists, creating...\n");
            channel = new_irc_channel(irc_server, channel_name);
        }
        if (!client_join_channel(irc_client, channel)) {
            printf("client can't join channel\n");
            //TODO:
            return 1;
        }

//        socket_send(&irc_client->fd, ":tounefr!~toune@80.214.70.47 JOIN #test * :realname\r\n");

        /*
        res = init_packet(NULL);
        packet_set(res, "JOIN", irc_client->realname);
        packet_set_params(res, 2, my_strdup(channel_name), "*");
        send_reply_packet(irc_client->fd, res);
         */

        send_RPL_TOPIC(irc_client, channel);

        //RPL_TOPIC
        //
    }
    free(channels_names);
    return 1;

}

char
on_privmsg_command(t_irc_server *irc_server,
                   t_irc_client *irc_client,
                   t_packet *packet)
{
    return 1;
}

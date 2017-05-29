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
on_join_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    t_packet *res;

    if (packet->nbr_params == 0) {
        res = init_packet(NULL);
        packet_set(res, "ERR_NEEDMOREPARAMS", "Not enough parameters");
        send_reply_packet(irc_client->fd, res);
        return 0;
    }

    char *channels_names;
    char *channel_name;
    t_irc_channel *channel;

    if (!(channels_names = strdup(packet->params[0])))
        malloc_error();
    while ((channel_name = strtok(channels_names, ","))) {
        channels_names = NULL;
        if (!(channel = irc_channel_exists(irc_server, channel_name)))
            channel = new_irc_channel(irc_server, channel_name);
        if (client_is_in_channel(channel, irc_client)) {
            //TODO:
        }
        if (!client_join_channel(irc_client, channel)) {
            //TODO:
        }
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

/*
** channel_commands2.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Fri Jun  9 10:40:53 2017 Thomas HENON
** Last update Fri Jun  9 10:40:54 2017 Thomas HENON
*/

#include "server.h"

char
on_privmsg_command(t_irc_server *irc_server,
                   t_client *irc_client,
                   t_packet *packet)
{
    char *channel_name;

    if (packet->nbr_params != 1)
        return 1;
    if (packet->params[0][0] == '#') {
        if (!(channel_name = normalize_channel_name(packet->params[0])))
            return 0;
        return send_msg_channel(irc_server, irc_client,
                                packet, channel_name);
    }
    else
        return send_msg_user(irc_server, irc_client, packet);
}

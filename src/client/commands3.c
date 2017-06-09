/*
** commands3.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc/src/client
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu Jun  8 18:08:48 2017 Thomas HENON
** Last update Thu Jun  8 18:08:50 2017 Thomas HENON
*/

#include "client.h"

char
on_NICK_command(t_irc_client *client,
                t_packet *packet)
{
    char *nick_src;
    char *new_nick;

    if (!packet->params[0] && !packet->content)
        return exit_error(0, "error\n");
    nick_src = parse_packet_prefix_dst(packet);
    new_nick = packet->params[0] ? packet->params[0] : packet->content;
    if (client->nickname && strcmp(nick_src, client->nickname)) {
        disp_message(INFO_LEVEL, "%s s'appelle maintenant %s",
            nick_src, new_nick);
        return 1;
    }
    client->nickname = my_strdup(new_nick);
    return disp_message(INFO_LEVEL, "Vous vous appelez maintenant : '%s'",
                 client->nickname);
}

char
on_ERR_NOSUCHNICK_command(t_irc_client *client,
                          t_packet *packet)
{
    (void)client;
    (void)packet;
    return 1;
}

char
on_welcome_command(t_irc_client *client,
                   t_packet *packet)
{
    (void)client;

    if (!packet->content)
        return 0;
    disp_message(INFO_LEVEL, "%s", packet->content);
    return 1;
}

char
on_NOTICE_command(t_irc_client *client,
                  t_packet *packet)
{
    (void)client;
    if (!packet->content)
        return 0;
    return disp_announce_message(packet->content);
}

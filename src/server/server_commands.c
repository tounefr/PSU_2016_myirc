/*
** server_commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:06:26 2017 Thomas HENON
** Last update Sun May 28 00:06:26 2017 Thomas HENON
*/

#include <stdlib.h>
#include "myirc.h"

char
on_nick_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    t_packet *res;

    if (packet->nbr_params == 0)
        return dprintf(irc_client->fd, "461 :Not enough parameters\r\n");
    if (check_pseudo_already_used(irc_server, packet->params[0])) {
        //TODO:
        return 0;
    }
    if (irc_client->pseudo)
        free(irc_client->pseudo);
    irc_client->pseudo = my_strdup(packet->params[0]);
    return 1;
}


char
on_names_command(t_irc_server *irc_server,
                 t_irc_client *irc_client,
                 t_packet *packet)
{
    return 1;
}

char
on_user_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    t_packet *res;

    if (packet->nbr_params != 3)
        return dprintf(irc_client->fd, "461 :Not enough parameters\r\n");
    irc_client->realname = my_strdup(packet->content);
    return dprintf(irc_client->fd, "001 %s :Welcome\r\n", irc_client->pseudo);
}

char
on_quit_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    socket_close(&irc_client->fd);
    on_exit_client(irc_server, irc_client);
    return 1;
}

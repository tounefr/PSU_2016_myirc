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
announce_nick_changed(t_irc_client *irc_client,
                      t_packet *packet)
{
    t_channels_list *registred_channels;
    t_irc_channel *irc_channel;
    t_clients_list *clients_in_channel;
    t_irc_client *client_in_channel;

    registred_channels = irc_client->registred_channels;
    while ((irc_channel = generic_list_foreach(registred_channels))) {
        registred_channels = NULL;
        clients_in_channel = irc_channel->clients;
        while ((client_in_channel = generic_list_foreach(clients_in_channel))) {
            clients_in_channel = NULL;
            if (client_in_channel == irc_client)
                continue;
            dprintf(client_in_channel->fd, ":%s NICK :%s\r\n", irc_client->pseudo, packet->params[0]);
        }
    }

}

char
on_nick_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    t_packet *res;

    if (packet->nbr_params == 0)
        return dprintf(irc_client->fd, "431 :No nickname given\r\n");
    if (check_pseudo_already_used(irc_server, packet->params[0]))
        return dprintf(irc_client->fd, "433 :Nickname is already in use\r\n");
    dprintf(irc_client->fd, ":%s NICK :%s\r\n", irc_client->pseudo, packet->params[0]);
    announce_nick_changed(irc_client, packet);
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
    irc_client->user = my_strdup(packet->params[0]);
    irc_client->realname = my_strdup(packet->content);
    dprintf(irc_client->fd, "001 %s :Welcome\r\n", irc_client->pseudo);

    return 1;
}

char
on_quit_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    on_exit_client(irc_server, irc_client);
    return 1;
}

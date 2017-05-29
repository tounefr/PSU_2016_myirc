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
    char *pseudo;
    t_packet *res;

    if (packet->nbr_params == 0) {
        res = init_packet(NULL);
        packet_set_param(packet, 0, pseudo);
        packet_set(res, "ERR_NONICKNAMEGIVEN", "No nickname given");
        send_reply_packet(irc_client->fd, res);
        return 0;
    }
    printf("%d\n", packet->nbr_params);
    pseudo = packet->params[0];
    if (check_pseudo_already_used(irc_server, pseudo)) {
        printf("pseudo already used\n");
        res = init_packet(NULL);
        packet_set_param(packet, 0, pseudo);
        packet_set(res, "ERR_NICKNAMEINUSE", "Nickname is already in use");
        send_reply_packet(irc_client->fd, res);
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

//TODO: ERR_ALREADYREGISTRED
char
on_user_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    t_packet *res;

    if (packet->nbr_params != 3) {
        res = init_packet(NULL);
        packet_set(res, "ERR_NEEDMOREPARAMS", "Not enough parameters");
        send_reply_packet(irc_client->fd, res);
        return 1;
    }
    irc_client->realname = my_strdup(packet->content);

    res = init_packet(NULL);
    packet_set(res, "MODE", "+i");
    packet_set_params(res, 1, irc_client->pseudo);
    send_reply_packet(irc_client->fd, res);

//    socket_send(&irc_client->fd, ":tounefr_ MODE tounefr_ :+i\r\n");

    /*res = init_packet(NULL);
    packet_set(res, "001", "Hello from TouneIRC!");
    packet_set_param(res, 0, irc_client->pseudo);
    send_reply_packet(irc_client->fd, res);*/
    return 1;
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

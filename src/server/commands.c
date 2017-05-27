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
        { "PRIVMSG", NULL, on_privmsg_command } // /msg ou $msg     1
};

char
on_join_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    if (packet->nbr_params == 0) {
        //ERR_NEEDMOREPARAMS
    }

}

char
on_list_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{

}

char
on_nick_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    char *pseudo;

    if (packet->nbr_params == 0) {
        //ERR_NONICKNAMEGIVEN
    }
    if (check_pseudo_already_used(irc_server, pseudo)) {
        //ERR_NICKNAMEINUSE
    }
    if (irc_client->pseudo)
        free(irc_client->pseudo);
    if (!(irc_client->pseudo = strdup(packet->params[0])))
        malloc_error();
    //OK
    socket_send(&irc_client->fd, "NOTICE * Hello world!\r\n");
}

char
on_part_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{

}

char
on_who_command(t_irc_server *irc_server,
               t_irc_client *irc_client,
               t_packet *packet)
{

}

char
on_names_command(t_irc_server *irc_server,
                 t_irc_client *irc_client,
                 t_packet *packet)
{

}

char
on_privmsg_command(t_irc_server *irc_server,
                   t_irc_client *irc_client,
                   t_packet *packet)
{

}
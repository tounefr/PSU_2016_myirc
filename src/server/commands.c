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
        { "PRIVMSG", content_with_spaces_parser, on_privmsg_command }, // /msg ou $msg     1
        { "USER", content_with_spaces_parser, on_user_command },
        { "QUIT", content_with_spaces_parser, on_quit_command }
};

char
on_list_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    return 1;
}


char
on_part_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet)
{
    return 1;
}

char
on_who_command(t_irc_server *irc_server,
               t_irc_client *irc_client,
               t_packet *packet)
{
    return 1;
}
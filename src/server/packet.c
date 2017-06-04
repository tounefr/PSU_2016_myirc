/*
** packet.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:03:04 2017 Thomas HENON
** Last update Sun Jun  4 12:03:04 2017 Thomas HENON
*/

#include "server.h"

char
parse_irc_packet(t_irc_server *irc_server,
                 t_client *irc_client,
                 t_packet *packet)
{
    int i;
    t_command_callback *cmd_call;

    if (!simple_space_parser(packet))
        return exit_error(0, "Failed to parse packet\n");
    i = -1;
    while (++i < N_COMMAND_CALLBACK) {
        cmd_call = &commands_callbacks[i];
        if (!strcmp(cmd_call->cmd, packet->cmd))
            return cmd_call->callback(irc_server, irc_client, packet);
    }
    return exit_error(0, "Unknown packet\n");
}

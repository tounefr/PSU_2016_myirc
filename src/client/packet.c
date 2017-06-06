/*
** packet.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:01:22 2017 Thomas HENON
** Last update Sun Jun  4 12:01:22 2017 Thomas HENON
*/

#include "client.h"

static char
match_packet_code(int code,
                  char *cmd)
{
    char code_str[10];

    if (!cmd)
        return 0;
    memset(code_str, 0, sizeof(code_str));
    if (code < 0)
        strcpy(code_str, "-1");
    else
        snprintf(code_str, sizeof(code_str) - 1, "%03d", code);
    return !strncmp(code_str, cmd, strlen(cmd));
}

char
parse_irc_packet(t_irc_client *irc_client,
                 t_packet *packet)
{
    int i;
    t_command_callback *cmd_call;

    if (!simple_space_parser(packet))
        return exit_error(0, "Failed to parse packet\n");
    i = -1;
    while (++i < N_COMMAND_CALLBACK) {
        cmd_call = &commands_callbacks[i];
        if (match_packet_code(cmd_call->code, packet->cmd) ||
                (cmd_call->cmd && !strcmp(cmd_call->cmd, packet->cmd)))
            return cmd_call->callback(irc_client, packet);
    }
    return 1;
    return exit_error(0, "Unknown packet\n");
}

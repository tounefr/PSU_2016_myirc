
#include "client.h"

static char
match_packet_code(int code,
                  char *cmd)
{
    char code_str[4];

    memset(code_str, 0, sizeof(code_str));
    snprintf(code_str, sizeof(code_str) - 1, "%d", code);
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
        if ((packet->cmd && !strcmp(cmd_call->cmd, packet->cmd)) ||
            match_packet_code(cmd_call->code, packet->cmd))
            return cmd_call->callback(irc_client, packet);
    }
    return exit_error(0, "Unknown packet\n");
}
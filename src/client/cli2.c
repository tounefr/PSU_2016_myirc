
#include "client.h"

char
on_cli_data(t_irc_client *irc_client)
{
    char *line;
    size_t n;

    line = NULL;
    n = 0;
    if ((getline(&line, &n, stdin)) != -1) {
        if (line[0] == '/') {
            if (!parse_cli_command(line, irc_client))
                disp_message(ERR_LEVEL, "Failed to parse command");
        }
        else
            send_channel_msg(line, irc_client);
    }
    return 1;
}
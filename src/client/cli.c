/*
** cli.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:00:50 2017 Thomas HENON
** Last update Sun Jun  4 12:00:50 2017 Thomas HENON
*/

#include "client.h"

char*
cmd_get_param(char *cmd,
              int p)
{
    int i;
    char *param;
    char *tmp;

    i = -1;
    tmp = my_strdup(cmd);
    while ((param = strtok(tmp, " "))) {
        tmp = NULL;
        if (++i == p)
            return my_strdup(param);
    }
    return NULL;
}

char
parse_cli_command(char *command,
                  t_irc_client *irc_client)
{
    int i;

    command[strlen(command)-1] = '\0';
    for (i = 0; i < N_CLI_COMMAND_CALLBACK; i++) {
        if (!strncmp(cli_commands_callbacks[i].cmd,
                     &command[1], strlen(cli_commands_callbacks[i].cmd))) {
            if ((cli_commands_callbacks[i].flags & FLAG_LOG_FIRST) &&
                !irc_client->logged) {
                printf("Log first\n");
                return 1;
            } else
                return cli_commands_callbacks[i].callback(irc_client, command);
        }
    }
    printf("Unknown command\n");
    return 1;
}

char
on_cli_data(t_irc_client *irc_client)
{
    char *line;
    size_t n;

//    printf("on_cli_data\n");
    if ((getline(&line, &n, stdin)) != -1) {
        if (line[0] == '/') {
            if (!parse_cli_command(line, irc_client))
                printf("Failed to parse command\n");
        }
        else
            send_channel_msg(line, irc_client);
    }
    return 1;
}

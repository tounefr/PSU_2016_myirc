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
disp_channel_message(char *pseudo,
                     char *channel,
                     char *message)
{
    char *date_prompt;

    date_prompt = get_prompt_date();
    printf("%s [#%s] <%s>: %s\n",
           date_prompt, channel,
            pseudo, message);
    free(date_prompt);
}

char
disp_message(char type,
             const char *message,
             ...)
{
    va_list args;

    va_start(args, message);
    printf("[INFO]: ");
    vprintf(message, args);
    printf("\n");
    va_end(args);
}

char*
get_prompt_date()
{
    time_t rawtime;
    struct tm *info;
    char *date_buffer;

    date_buffer = my_malloc(100);
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(date_buffer, 99, "%d/%m/%Y %H:%M", info);
    return date_buffer;
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
                return disp_message(WARN_LEVEL, "Log first");
            } else
                return cli_commands_callbacks[i].callback(irc_client, command);
        }
    }
    disp_message(ERR_LEVEL, "Unknown command");
    return 1;
}
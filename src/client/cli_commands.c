/*
** cli_commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:00:56 2017 Thomas HENON
** Last update Sun Jun  4 12:00:57 2017 Thomas HENON
*/

#include "client.h"

t_cli_command_callback cli_commands_callbacks[N_CLI_COMMAND_CALLBACK] =
{
    { "server", on_server_cli_command, FLAG_NONE },
    { "nick", on_nick_cli_command, FLAG_LOG_FIRST },
    { "list", on_list_cli_command, FLAG_LOG_FIRST },
    { "join", on_join_cli_command, FLAG_LOG_FIRST },
    { "part", on_part_cli_command, FLAG_LOG_FIRST },
    { "users", on_users_cli_command, FLAG_LOG_FIRST },
    { "names", on_names_cli_command, FLAG_LOG_FIRST },
    { "msg", on_msg_cli_command, FLAG_LOG_FIRST },
    { "accept_file", on_accept_file_cli_command, FLAG_LOG_FIRST }
};

char
split_host_port(char *host_port,
                char **host,
                unsigned short *port)
{
    char *tmp;
    int i;
    char *param;
    char returnv;

    returnv = 1;
    i = 0;
    host_port = my_strdup(host_port);
    tmp = host_port;
    while ((param = strtok(host_port, ":"))) {
        host_port = NULL;
        if (i == 0)
            *host = my_strdup(param);
        else if (i == 1)
            *port = atoi(param);
        else {
            returnv = 0;
            break;
        }
        i++;
    }
    if (i != 2)
        returnv = 0;
    free(tmp);
    return returnv;
}

void
identify_me(t_irc_client *irc_client, char *nickname)
{
    //generate_nickname
    dprintf(irc_client->fd, "NICK %s\r\n", nickname);
    dprintf(irc_client->fd, "USER %s %s %s :%s\r\n",
            nickname, "127.0.0.1",
            IRC_SERVER_HOST, "real name");
}

char
on_server_cli_command(t_irc_client *irc_client,
                      char *cmd)
{
    char *host_port;
    char *host;
    unsigned short port;

    if (irc_client->logged)
        return printf("Vous êtes déjà connecté\n");
    if (!(host_port = cmd_get_param(cmd, 1)))
        exit_error(0, "error\n");
    if (!split_host_port(host_port, &host, &port))
        exit_error(0, "error\n");
    printf("Tentative de connexion vers %s:%d ...\n", host, port);
    if (!socket_connect(&irc_client->fd, host, &port)) {
        printf("Impossible de se connecter\n");
        return 1;
    }
    irc_client->logged = 1;
    printf("Connecté !\n");
    identify_me(irc_client, generate_nickname());
    return 1;
}

char
on_nick_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *nickname;

    if (!(nickname = cmd_get_param(cmd, 1)))
        exit_error(0, "error\n");
    identify_me(irc_client, nickname);
    return 1;
}

char
on_list_cli_command(t_irc_client *irc_client,
                    char *cmd)
{

}

char
on_join_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *channel;

    if (!(channel = cmd_get_param(cmd, 1)))
        exit_error(0, "error\n");
    if (!(channel = normalize_channel_name(channel)))
        exit_error(0, "error\n");
    dprintf(irc_client->fd, "JOIN #%s\r\n", channel);
    return 1;
}

char
on_part_cli_command(t_irc_client *irc_client,
                    char *cmd)
{

}

char
on_users_cli_command(t_irc_client *irc_client,
                     char *cmd)
{

}

char
on_names_cli_command(t_irc_client *irc_client,
                     char *cmd)
{

}

char
on_msg_cli_command(t_irc_client *irc_client,
                   char *cmd)
{

}

char
on_accept_file_cli_command(t_irc_client *irc_client,
                           char *cmd)
{

}

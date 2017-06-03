
#include "client.h"

t_cli_command_callback cli_commands_callbacks[N_CLI_COMMAND_CALLBACK] =
{
        { "server", on_server_cli_command, 0 },
        { "nick", on_nick_cli_command, 0 },
        { "list", on_list_cli_command, 0 },
        { "join", on_join_cli_command, 0 },
        { "part", on_part_cli_command, 0 },
        { "users", on_users_cli_command, 0 },
        { "names", on_names_cli_command, 0 },
        { "msg", on_msg_cli_command, 0 },
        { "accept_file", on_accept_file_cli_command, 0 }
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

char
on_server_cli_command(t_irc_client *irc_client,
                      char *cmd)
{
    char *host_port;
    char *host;
    unsigned short port;

    if (!(host_port = cmd_get_param(cmd, 1)))
        exit_error(0, "error\n");
    if (!split_host_port(host_port, &host, &port))
        exit_error(0, "error\n");
    printf("Tentative de connexion vers %s:%d ...\n", host, port);
    if (!socket_connect(&irc_client->fd, host, &port))
        printf("Impossible de se connecter\n");
    else
        printf("Connecté !\n");
    return 1;
}

char
on_nick_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *nickname;

    if (!(nickname = cmd_get_param(cmd, 1)))
        exit_error(0, "error\n");
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
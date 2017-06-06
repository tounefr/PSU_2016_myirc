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

static char
split_it(char *host_port, char **host, unsigned short *port)
{
    char *tmp;
    int i;
    char *param;
    int returnv;

    i = 0;
    host_port = my_strdup(host_port);
    tmp = host_port;
    returnv = 1;
    *port = DEFAULT_SERVER_PORT;
    while ((param = strtok(host_port, ":"))) {
        host_port = NULL;
        if (i == 0)
            *host = my_strdup(param);
        else if (i == 1 && is_number(param))
            *port = atoi(param);
        else {
            returnv = 0;
            break;
        }
        i++;
    }
    free(tmp);
    return returnv;
}

char
split_host_port(char *host_port,
                char **host,
                unsigned short *port)
{
    char returnv;
    char *hostname;

    if (!split_it(host_port, host, port))
        return 0;
    hostname = *host;
    if (!is_ipv4(*host) && !(*host = resolve_hostname(*host)))
        return exit_error(0, "Failed to fetch %s\n", hostname);
    return 1;
}

void
identify_me(t_irc_client *irc_client, char *nickname)
{
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
        return disp_message(INFO_LEVEL, "Vous êtes déjà connecté");
    if (!(host_port = cmd_get_param(cmd, 1)))
        return exit_error(0, "error\n");
    if (!split_host_port(host_port, &host, &port))
        return exit_error(0, "error\n");
    disp_message(INFO_LEVEL, "Tentative de connexion vers %s:%d ...",
                 host, port);
    if (!socket_init(&irc_client->fd) ||
        !socket_connect(&irc_client->fd, host, &port))
        return disp_message(WARN_LEVEL, "Impossible de se connecter");
    irc_client->logged = 1;
    disp_message(INFO_LEVEL, "Connecté !");
    identify_me(irc_client, generate_nickname());
    return 1;
}

char
on_nick_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *nickname;

    if (!(nickname = cmd_get_param(cmd, 1)))
        return exit_error(0, "error\n");
    identify_me(irc_client, nickname);
    return 1;
}

char
on_list_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *channel_name;

    if ((channel_name = cmd_get_param(cmd, 1))) {
        if (!(channel_name = normalize_channel_name(channel_name)))
            return exit_error(0, "normalize_channel_name\n");
        return dprintf(irc_client->fd, "LIST #%s\r\n", channel_name);
    }
    else
        return dprintf(irc_client->fd, "LIST\r\n");
}

char
on_join_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *channel;

    if (!(channel = cmd_get_param(cmd, 1)))
        return exit_error(0, "error\n");
    if (!(channel = normalize_channel_name(channel)))
        return exit_error(0, "error\n");
    if (irc_client->cur_channel)
        return disp_message(INFO_LEVEL,
                            "Vous ne pouvez pas être connecté "
                            "à 2 channels en même temps");
    dprintf(irc_client->fd, "JOIN #%s\r\n", channel);
    return 1;
}

char
on_part_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *channel_name;

    if (!(channel_name = cmd_get_param(cmd, 1)))
        return exit_error(0, "error\n");
    if (!(channel_name = normalize_channel_name(channel_name)))
        return exit_error(0, "error\n");
    printf("%s %s\n", irc_client->cur_channel->name, channel_name);
    if (!irc_client->cur_channel ||
            strcmp(irc_client->cur_channel->name, channel_name))
        return exit_error(0, "Vous n'êtes pas connecté à ce channel\n");
    dprintf(irc_client->fd, "PART #%s\r\n", irc_client->cur_channel->name);
}
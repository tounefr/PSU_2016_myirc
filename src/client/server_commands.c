/*
** server_commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc/src/client
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu Jun  8 18:07:58 2017 Thomas HENON
** Last update Thu Jun  8 18:07:58 2017 Thomas HENON
*/

#include "client.h"

static char
split_it(char *host_port,
         char **host,
         unsigned short *port)
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

static char
split_host_port(char *host_port,
                char **host,
                unsigned short *port)
{
    char returnv;
    char *hostname;

    if (!split_it(host_port, host, port))
        return !disp_message(ERR_LEVEL, "Wrong usage");
    hostname = *host;
    if (!is_ipv4(*host) && !(*host = resolve_hostname(*host)))
        return !disp_message(ERR_LEVEL, "Failed to resolve \"%s\"",
                             hostname);
    return 1;
}

static void
identify_me(t_irc_client *irc_client,
            char *nickname)
{
    dprintf(irc_client->fd, "NICK %s\r\n", nickname);
    dprintf(irc_client->fd, "USER %s %s %s :%s\r\n",
            nickname, nickname,
            "127.0.0.1", nickname);
    irc_client->nickname = my_strdup(nickname);
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
        return disp_message(ERR_LEVEL, "Wrong usage");
    if (!split_host_port(host_port, &host, &port))
        return 0;
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

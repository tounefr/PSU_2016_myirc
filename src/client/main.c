/*
** main.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:16:59 2017 Thomas HENON
** Last update Sat May 27 20:16:59 2017 Thomas HENON
*/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"

t_irc_client *
get_irc_client()
{
    static t_irc_client irc_client;
    return &irc_client;
}

void
sigint_handler(int signum)
{
    if (signum != SIGINT)
        return;

    exit(1);
}

char*
cmd_get_param(char *cmd, int p)
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

int
my_select(t_my_select *ss,
          t_irc_client *irc_client)
{
    init_my_select(ss);
    add_readfd_my_select(ss, 0);
    if (irc_client->fd != -1)
        add_readfd_my_select(ss, irc_client->fd);
//    add_readfd_clients(ss, irc_client->irc_clients);
    ss->nfds = 1;
    return select(ss->nfds, &ss->readfds,
                  &ss->writefds, &ss->exceptfds,
                  &ss->timeout);
}

char
parse_cli_command(char *command,
                  t_irc_client *irc_client)
{
    int i;

    command[strlen(command)-1] = '\0';
    for (i = 0; i < N_CLI_COMMAND_CALLBACK; i++) {
        if (!strncmp(cli_commands_callbacks[i].cmd,
                     &command[1], strlen(cli_commands_callbacks[i].cmd)))
            return cli_commands_callbacks[i].callback(irc_client, command);
    }
    printf("Unknown command\n");
    return 1;
}

char
send_channel_msg(char *command,
                 t_irc_client *irc_client)
{

}

char
on_cli_data(t_irc_client *irc_client)
{
    char *line;
    size_t n;

    while ((getline(&line, &n, stdin)) != -1) {
        if (line[0] == '/' && !parse_cli_command(line, irc_client))
            printf("Failed to parse command\n");
        else
            send_channel_msg(line, irc_client);
    }
    return 0;
}

char
on_network_data(t_irc_client *irc_client)
{
    char        buffer[BUFFER_SIZE];
    int         readv;
    char        *raw;
    t_packet    *packet;
    char        returnv;

    if ((readv = read(irc_client->fd, buffer, BUFFER_SIZE)) <= 0) {
        //on_exit_client(irc_server, irc_client);
        printf("client exit\n");
        return 0;
    }
    cbuffer_copy(irc_client->cbuffer, buffer, readv);
    //EXIT_ERROR(0, "cbuffer_extract failed\n")
    while ((raw = cbuffer_extract(irc_client->cbuffer,
                                  IRC_PACKET_SIZE,
                                  "\r\n"))) {
        packet = init_packet(raw);
        printf("Recv << %s", raw);
        //returnv = parse_irc_packet(irc_server, irc_client, packet);
        free_packet(packet);
    }
    return 1;
}

char
client_select_on_data(t_irc_client *irc_client)
{
    if (FD_ISSET(0, &irc_client->my_select.readfds))
        return on_cli_data(irc_client);
    else if (FD_ISSET(irc_client->fd,
                      &irc_client->my_select.readfds))
        return on_network_data(irc_client);
    return 0;
}

char
init_irc_client(t_irc_client *irc_client)
{
    irc_client->registrated_channels = NULL;
    irc_client->cbuffer = NULL;
    if (!socket_init(&irc_client->fd))
        return 0;
    return 1;
}

char
start_irc_client()
{
    t_irc_client *irc_client;
    int retrv;

    irc_client = get_irc_client();
    if (!init_irc_client(irc_client))
        return 0;
    while (1) {
        retrv = my_select(&irc_client->my_select, irc_client);
        if (retrv == 0) {
            //printf("no data\n");
        }
        else if (retrv == -1)
            return exit_error(0, "select error : %s\n", strerror(errno));
        else if (!client_select_on_data(irc_client))
            return 0;
    }
    return 1;
}

int
main() {
    signal(SIGINT, sigint_handler);
    return !start_irc_client();
}

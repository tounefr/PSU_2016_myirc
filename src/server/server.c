/*
** server.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:18:17 2017 Thomas HENON
** Last update Sat May 27 20:18:18 2017 Thomas HENON
*/

#include <stdlib.h>
#include <unistd.h>
#include "myirc.h"

char        init_irc_server(t_irc_server *irc_server)
{
    if (!socket_init(&irc_server->fd_server))
        return 0;
    if (!socket_listen(&irc_server->fd_server,
                       irc_server->listen_address,
                       &irc_server->listen_port))
        return 0;
    irc_server->irc_clients = NULL;
    return 1;
}

char    on_server_new_client(t_irc_server *irc_server)
{
    int fd_new_client;

    if (!socket_accept(&irc_server->fd_server, &fd_new_client))
        return 0;
    new_irc_client(irc_server, fd_new_client);
    printf("New client !\n");
    return 1;
}

char                on_exit_client(t_irc_server *irc_server,
                                   t_irc_client *irc_client)
{
    t_irc_client    *cur;
    t_irc_client    *prev;
    t_irc_client    *next;

    cur = irc_server->irc_clients;
    prev = NULL;
    while (cur) {
        next = cur->next;
        if (cur == irc_client) {
            if (prev)
                prev->next = cur->next;
            else
                irc_server->irc_clients = NULL;
            break;
        }
        prev = cur;
        cur = next;
    }
    socket_close(&irc_client->fd);
    free(irc_client);
    return 1;
}

char            on_client_data(t_irc_server *irc_server,
                           t_irc_client *irc_client)
{
    char        buffer[BUFFER_SIZE];
    int         readv;
    char        *raw;
    t_packet    *packet;
    char        returnv;

    if ((readv = read(irc_client->fd, buffer, BUFFER_SIZE)) <= 0) {
        on_exit_client(irc_server, irc_client);
        printf("client exit\n");
        return 0;
    }
    cbuffer_copy(irc_client->cbuffer, buffer, readv);
    if (!(raw = cbuffer_extract(irc_client->cbuffer,
                                   IRC_PACKET_SIZE,
                                   "\r\n")))
        EXIT_ERROR(0, "cbuffer_extract failed\n")
    packet = init_packet(raw);
    printf("Recv << %s", raw);
    returnv = parse_irc_packet(irc_server, irc_client, packet);
    //free_packet(packet);
    return returnv;
}

char                server_select_on_data(t_server_select *ss,
                                          t_irc_server *irc_server)
{
    t_irc_client    *client;
    t_irc_client    *next;

    if (FD_ISSET(irc_server->fd_server, &ss->readfds)) {
        if (!on_server_new_client(irc_server))
            return 0;
    }
    client = irc_server->irc_clients;
    while (client) {
        next = client->next;
        if (FD_ISSET(client->fd, &ss->readfds))
            on_client_data(irc_server, client);
        client = next;
    }
    return 1;
}

char                start_irc_server(t_irc_server *irc_server)
{
    t_server_select ss;
    int             retrv;

    if (!init_irc_server(irc_server))
        return 0;
    while (1) {
        retrv = my_select(&ss, irc_server);
        if (retrv == 0) {

        }
        else if (retrv == -1) {
            printf("select error : %s\n", strerror(errno));
            break;
        }
        else if (!server_select_on_data(&ss, irc_server)) {
            break;
        }
    }
    socket_close(&irc_server->fd_server);
    return 1;
}

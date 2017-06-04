/*
** server.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:18:17 2017 Thomas HENON
** Last update Sat May 27 20:18:18 2017 Thomas HENON
*/

#include "server.h"

char
init_irc_server(t_irc_server *irc_server)
{
    if (!socket_init(&irc_server->fd_server))
        return 0;
    if (!socket_listen(&irc_server->fd_server,
                       irc_server->listen_address,
                       &irc_server->listen_port))
        return 0;
    irc_server->channels = NULL;
    irc_server->irc_clients = NULL;
    return 1;
}

char
on_server_new_client(t_irc_server *irc_server)
{
    int fd_new_client;

    if (!socket_accept(&irc_server->fd_server, &fd_new_client))
        return 0;
    new_irc_client(irc_server, fd_new_client);
    printf("New client !\n");
    return 1;
}

char
on_exit_client(t_irc_server *irc_server,
               t_client *irc_client)
{
    t_channels_list *channels_list;
    t_channel *channel;

    channels_list = irc_client->registred_channels;
    while ((channel = generic_list_foreach(channels_list))) {
        channels_list = NULL;
        announce_channel_client_part(irc_client, channel);
        generic_list_remove(&channel->clients, irc_client, NULL);
    }
    socket_close(&irc_client->fd);
    generic_list_remove(&irc_server->irc_clients, irc_client, NULL);//TODO: fix NULL
    return 1;
}

char
on_client_data(t_irc_server *irc_server,
               t_client *irc_client)
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
    //EXIT_ERROR(0, "cbuffer_extract failed\n")
    while ((raw = cbuffer_extract(irc_client->cbuffer,
                                  IRC_PACKET_SIZE,
                                  "\r\n"))) {
        packet = init_packet(raw);
        printf("Recv << %s", raw);
        returnv = parse_irc_packet(irc_server, irc_client, packet);
        free_packet(packet);
    }
    return 1;
}

char
server_select_on_data(t_my_select *ss,
                      t_irc_server *irc_server)
{
    t_client    *client;
    t_clients_list  *clients;
    t_client    *next;

    if (FD_ISSET(irc_server->fd_server, &ss->readfds)) {
        if (!on_server_new_client(irc_server))
            return 0;
    }
    clients = irc_server->irc_clients;
    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
        if (FD_ISSET(client->fd, &ss->readfds))
            on_client_data(irc_server, client);
    }
    return 1;
}

char
start_irc_server(t_irc_server *irc_server)
{
    t_my_select ss;
    int retrv;

    if (!init_irc_server(irc_server))
        return 0;
    while (1) {
        retrv = my_select(&ss, irc_server);
        if (retrv == 0) {
            /*printf("There is %d clients connected and %d channels\n",
                   generic_list_count(irc_server->irc_clients),
                   generic_list_count(irc_server->channels));*/
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
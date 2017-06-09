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
server_select_on_data(t_my_select *ss,
                      t_irc_server *irc_server)
{
    t_client    *client;
    t_clients_list  *clients;

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
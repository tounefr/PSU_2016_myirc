/*
** socket2.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myftp
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu May 18 10:33:07 2017 Thomas HENON
** Last update Thu May 18 10:33:07 2017 Thomas HENON
*/

#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "socket.h"

char
socket_port_used(unsigned short port)
{
    int fd;

    if (!socket_init(&fd))
        return 1;
    if (!socket_listen(&fd, "0.0.0.0", &port)) {
        socket_close(&fd);
        return 1;
    }
    socket_close(&fd);
    return 0;
}

void
free_socket_infos(t_socket_infos *socket_infos)
{
    if (!socket_infos)
        return;
    if (socket_infos->client_ipv4)
        free(socket_infos->client_ipv4);
    if (socket_infos->server_ipv4)
        free(socket_infos->server_ipv4);
}
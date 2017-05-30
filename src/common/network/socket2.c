/*
** socket2.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myftp
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu May 18 10:33:07 2017 Thomas HENON
** Last update Thu May 18 10:33:07 2017 Thomas HENON
*/

#include <arpa/inet.h>
#include <sys/socket.h>
#include "socket.h"
#include "socket_server.h"

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

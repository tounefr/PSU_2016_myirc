/*
** socket.h for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:04:00 2017 Thomas HENON
** Last update Sun May 28 00:04:01 2017 Thomas HENON
*/

#ifndef PROJETS_SOCKET_H
#define PROJETS_SOCKET_H

typedef struct s_socket_infos
{
    char            *client_ipv4;
    unsigned short  client_port;
    char            client_hostname[1024];
    char            *server_ipv4;
    unsigned short  server_port;
} t_socket_infos;

char socket_init(int *fd);
char socket_connect(int *fd, char *ip, unsigned short *port);
char socket_infos(int *socket_fd, t_socket_infos *socket_infos);
char socket_send(int *fd, char *buffer);
char socket_close(int *fd);
char socket_port_used(unsigned short port);

#endif //PROJETS_SOCKET_H

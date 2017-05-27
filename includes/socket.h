//
// Created by toune on 26/05/17.
//

#ifndef PROJETS_SOCKET_H
#define PROJETS_SOCKET_H

typedef struct s_socket_infos
{
    char            *client_ipv4;
    unsigned short  client_port;
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

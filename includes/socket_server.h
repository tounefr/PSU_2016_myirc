//
// Created by toune on 26/05/17.
//

#ifndef PROJETS_SOCKET_SERVER_H
#define PROJETS_SOCKET_SERVER_H

char socket_accept(int *server_socket, int *client_socket);
char socket_listen(int *server_fd,
                   char *listen_address,
                   unsigned short *listen_port);

#endif //PROJETS_SOCKET_SERVER_H

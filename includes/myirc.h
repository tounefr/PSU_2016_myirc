
#ifndef PROJETS_MYIRC_H
#define PROJETS_MYIRC_H

#include "socket.h"

/*
typedef struct s_irc_client
{
    int                 socket_fd;
    t_socket_infos      socket_infos;
} t_irc_client;
*/

# define LISTEN_ADDRESS "0.0.0.0"
# define BUFFER_SIZE 512

typedef struct      s_server_select
{
    int             nfds;
    int             readfds_n;
    fd_set          readfds;
    fd_set          writefds;
    int             writefds_n;
    struct timeval  timeout;
    fd_set          exceptfds;
} t_server_select;

typedef struct          s_irc_client
{
    int                 fd;
    char                buffer[BUFFER_SIZE];
    struct s_irc_client *next;

} t_irc_client;

typedef struct      s_irc_server
{
    int             fd_server;
    char            *listen_address;
    unsigned short  listen_port;
    t_irc_client    *irc_clients;

} t_irc_server;

#endif //PROJETS_MYIRC_H

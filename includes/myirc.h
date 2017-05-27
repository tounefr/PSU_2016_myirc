/*
** myirc.h for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:03:53 2017 Thomas HENON
** Last update Sun May 28 00:03:53 2017 Thomas HENON
*/

#ifndef PROJETS_MYIRC_H
#define PROJETS_MYIRC_H

/*
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
 */

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

#include "util.h"
#include "socket.h"
#include "socket_server.h"

# define LISTEN_ADDRESS "0.0.0.0"
# define BUFFER_SIZE 512
# define IRC_PACKET_SIZE 512
# define IRC_CLIENT_MAX_CHANNELS 10
# define IRC_SERVER_MAX_CHANNELS 100
# define IRC_PACKET_NBR_PARAMS 15
# define IRC_CHANNEL_MAX_CLIENTS 100

typedef struct s_circular_buffer
{
    int size;
    int cur_off;
    char *buffer;
} t_circular_buffer;

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

typedef struct s_irc_client t_irc_client;
typedef struct      s_irc_channel
{
    char            *name;
    int             max_clients;
    t_irc_client    *clients;
    t_irc_client    *op;
} t_irc_channel;

typedef struct          s_irc_client
{
    char                *pseudo;
    int                 fd;
    t_circular_buffer   *cbuffer;
    t_irc_channel       *registred_channels;
    struct s_irc_client *next;
} t_irc_client;

typedef struct      s_irc_server
{
    int             fd_server;
    char            *listen_address;
    unsigned short  listen_port;
    t_irc_channel   *channels;
    t_irc_client    *irc_clients;
} t_irc_server;

typedef struct s_packet
{
    char        *raw;
    char        *cmd;
    int         nbr_params;
    char        *params[IRC_PACKET_NBR_PARAMS];
    char        *content;
} t_packet;

# define N_COMMAND_CALLBACK 7
typedef struct s_command_callback
{
    char *cmd;
    char (*parser)(t_packet *packet);
    char (*callback)(t_irc_server*, t_irc_client*, t_packet *);
} t_command_callback;
extern t_command_callback commands_callbacks[N_COMMAND_CALLBACK];

// my_select.c
int my_select(t_server_select *ss, t_irc_server *irc_server);

// cbuffer.c
t_circular_buffer       *cbuffer_new(int size);
void    cbuffer_debug(t_circular_buffer *cbuffer);
char cbuffer_get_char_at(t_circular_buffer *cbuffer, int i);
void    cbuffer_copy(t_circular_buffer *cbuffer,
                     char *buff,
                     int buff_size);
char        *cbuffer_extract(t_circular_buffer *cbuffer,
                             int packet_size,
                             char *delim);

// client.c
void    init_irc_client(t_irc_client *irc_client, int fd);
void                new_irc_client(t_irc_server *irc_server,
                                   int fd_new_client);

// server.c
char        init_irc_server(t_irc_server *irc_server);
char    on_server_new_client(t_irc_server *irc_server);
char                on_exit_client(t_irc_server *irc_server,
                                   t_irc_client *irc_client);
char        on_client_data(t_irc_server *irc_server,
                           t_irc_client *irc_client);
char                server_select_on_data(t_server_select *ss,
                                          t_irc_server *irc_server);
char                start_irc_server(t_irc_server *irc_server);

// commands.c

char
on_join_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet);

char
on_list_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet);

char
on_nick_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet);

char
on_part_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet);

char
on_who_command(t_irc_server *irc_server,
               t_irc_client *irc_client,
               t_packet *packet);

char
on_names_command(t_irc_server *irc_server,
                 t_irc_client *irc_client,
                 t_packet *packet);

char
on_privmsg_command(t_irc_server *irc_server,
                   t_irc_client *irc_client,
                   t_packet *packet);

// packet_parser.c
char simple_space_parser(t_packet *packet);
char *strdup_irc_packet(char *buffer);

// packet.c
t_packet *init_packet(char *raw);
void free_packet(t_packet *packet);
char parse_irc_packet(t_irc_server *irc_server,
                      t_irc_client *irc_client,
                      t_packet *packet);
char send_reply_packet(int fd, int code, char *buffer);

// error.c
char exit_error(int returnv);
void malloc_error();

// channel_commands.c
char check_pseudo_already_used(t_irc_server *irc_server, char *pseudo);

#endif //PROJETS_MYIRC_H

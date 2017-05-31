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

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdarg.h>
#include <stdio.h>

#include "util.h"
#include "socket.h"
#include "socket_server.h"
#include "generic_list.h"

# define LISTEN_ADDRESS "0.0.0.0"
# define BUFFER_SIZE 512
# define IRC_PACKET_SIZE 512
# define IRC_CLIENT_MAX_CHANNELS 10
# define IRC_SERVER_MAX_CHANNELS 100
# define IRC_PACKET_NBR_PARAMS 15
# define IRC_CHANNEL_MAX_CLIENTS 100
# define IRC_SERVER_HOST "irc.lan"

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

typedef t_generic_list t_channels_list;
typedef t_generic_list t_clients_list;

typedef struct s_irc_client t_irc_client;
typedef struct      s_irc_channel
{
    char            *name;
    char            *topic;
    int             max_clients;
    t_clients_list  *clients;
    t_irc_client    *op;
} t_irc_channel;

typedef struct          s_irc_client
{
    char                *pseudo;
    char                *user;
    char                *realname;
    char                logged;
    int                 fd;
    t_circular_buffer   *cbuffer;
    t_socket_infos      socket_infos;
    t_channels_list     *registred_channels;
} t_irc_client;

typedef struct      s_irc_server
{
    int             fd_server;
    char            *listen_address;
    unsigned short  listen_port;
    t_channels_list *channels;
    t_clients_list  *irc_clients;
} t_irc_server;

typedef struct s_packet
{
    char        *raw;
    char        *prefix;
    char        *cmd;
    int         nbr_params;
    int         code;
    char        *params[IRC_PACKET_NBR_PARAMS];
    char        *content;
} t_packet;

# define N_COMMAND_CALLBACK 12

# define FLAG_NONE 0
# define FLAG_LOG_FIRST 1
typedef struct s_command_callback
{
    char *cmd;
    char (*callback)(t_irc_server*, t_irc_client*, t_packet *);
    char flags;
} t_command_callback;
extern t_command_callback commands_callbacks[N_COMMAND_CALLBACK];

// my_select.c
int my_select(t_server_select *ss, t_irc_server *irc_server);

// cbuffer.c
void
cbuffer_free(t_circular_buffer *cbuffer);
t_circular_buffer       *cbuffer_new(int size);
void    cbuffer_debug(t_circular_buffer *cbuffer);
char cbuffer_get_char_at(t_circular_buffer *cbuffer, int i);
void cbuffer_set_char_at(t_circular_buffer *cbuffer,
                         int i,
                         char c);
void    cbuffer_copy(t_circular_buffer *cbuffer,
                     char *buff,
                     int buff_size);
char        *cbuffer_extract(t_circular_buffer *cbuffer,
                             int packet_size,
                             char *delim);

// main.c
t_irc_server *get_irc_server();

// client.c
void    init_irc_client(t_irc_client *irc_client, int fd);
void                new_irc_client(t_irc_server *irc_server,
                                   int fd_new_client);
char
free_irc_client(void *data);

// server.c
void
sigint_handler(int signum);
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
on_whois_command(t_irc_server *irc_server,
                 t_irc_client *irc_client,
                 t_packet *packet);

char
announce_channel_client_part(t_irc_client *irc_client,
                             t_irc_channel *irc_channel);

char
on_ping_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet);

char
on_mode_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet);

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

char
on_user_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet);

char
on_quit_command(t_irc_server *irc_server,
                t_irc_client *irc_client,
                t_packet *packet);

// packet_parser.c
char simple_space_parser(t_packet *packet);
char content_with_spaces_parser(t_packet *packet);
char *strdup_irc_packet(char *buffer);

// packet.c
t_packet *init_packet(char *raw);
void free_packet(t_packet *packet);
char parse_irc_packet(t_irc_server *irc_server,
                      t_irc_client *irc_client,
                      t_packet *packet);
void packet_set(t_packet *packet, char *cmd, char *content);
void packet_set_param(t_packet *packet, int i, char *param);
void packet_set_params(t_packet *packet, int nbr_params, ...);
char buffer_rm_crlf(char *buffer);
char send_reply_packet(int fd, t_packet *res);

// error.c
void malloc_error();

// channel.c
t_irc_channel *new_irc_channel(t_irc_server *irc_server, char *name);
char* normalize_channel_name(char *channel);
t_irc_channel *irc_channel_exists(t_irc_server *irc_server, char *name);
char client_join_channel(t_irc_client *client, t_irc_channel *channel);
char client_is_in_channel(t_irc_channel *channel, t_irc_client *to_find);
char client_leave_channel(t_irc_client *client, t_irc_channel *channel);
char free_irc_channel(void *data);

// channel_commands.c
char check_pseudo_already_used(t_irc_server *irc_server, char *pseudo);

#endif //PROJETS_MYIRC_H

/*
** server.h for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:04:38 2017 Thomas HENON
** Last update Sun Jun  4 12:04:39 2017 Thomas HENON
*/

#ifndef PROJETS_SERVER_H
#define PROJETS_SERVER_H

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdarg.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"

typedef struct          s_client
{
    char                *pseudo;
    char                *user;
    char                *realname;
    char                logged;
    int                 fd;
    t_circular_buffer   *cbuffer;
    t_socket_infos      socket_infos;
    t_channels_list     *registred_channels;
} t_client;

typedef struct      s_irc_server
{
    int             fd_server;
    char            *listen_address;
    unsigned short  listen_port;
    t_channels_list *channels;
    t_clients_list  *irc_clients;
} t_irc_server;

# define N_COMMAND_CALLBACK 12
typedef struct s_command_callback
{
    char *cmd;
    char (*callback)(t_irc_server*, t_client*, t_packet *);
    char flags;
} t_command_callback;
extern t_command_callback commands_callbacks[N_COMMAND_CALLBACK];

// my_select.c
int my_select(t_my_select *ss, t_irc_server *irc_server);


// main.c
t_irc_server *get_irc_server();

// client.c
void    init_client(t_client *irc_client, int fd);
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
                                   t_client *irc_client);
char        on_client_data(t_irc_server *irc_server,
                           t_client *irc_client);
char                server_select_on_data(t_my_select *ss,
                                          t_irc_server *irc_server);
char                start_irc_server(t_irc_server *irc_server);

// commands.c

char
on_whois_command(t_irc_server *irc_server,
                 t_client *irc_client,
                 t_packet *packet);

char
announce_channel_client_part(t_client *irc_client,
                             t_channel *irc_channel);

char
on_ping_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet);

char
on_mode_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet);

char
on_join_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet);

char
on_list_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet);

char
on_nick_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet);

char
on_part_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet);

char
on_who_command(t_irc_server *irc_server,
               t_client *irc_client,
               t_packet *packet);

char
on_names_command(t_irc_server *irc_server,
                 t_client *irc_client,
                 t_packet *packet);

char
on_privmsg_command(t_irc_server *irc_server,
                   t_client *irc_client,
                   t_packet *packet);

char
on_user_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet);

char
on_quit_command(t_irc_server *irc_server,
                t_client *irc_client,
                t_packet *packet);

// packet_parser.c
char simple_space_parser(t_packet *packet);
char content_with_spaces_parser(t_packet *packet);
char *strdup_irc_packet(char *buffer);
char
parse_irc_packet(t_irc_server *irc_server,
                 t_client *irc_client,
                 t_packet *packet);;

// error.c
void malloc_error();

// channel.c
char client_join_channel(t_client *client, t_channel *channel);
char client_is_in_channel(t_channel *channel, t_client *to_find);
char client_leave_channel(t_client *client, t_channel *channel);
char free_channel(void *data);

// channel_commands.c
char check_pseudo_already_used(t_irc_server *irc_server, char *pseudo);

#endif //PROJETS_SERVER_H

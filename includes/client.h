/*
** client.h for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:04:07 2017 Thomas HENON
** Last update Sun Jun  4 12:04:07 2017 Thomas HENON
*/

#ifndef PROJETS_CLIENT_H
#define PROJETS_CLIENT_H

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "common.h"

# define N_CLI_COMMAND_CALLBACK 9
typedef struct s_irc_client t_irc_client;
typedef struct s_cli_command_callback
{
    char *cmd;
    char (*callback)(t_irc_client*, char*);
    char flags;
} t_cli_command_callback;
extern t_cli_command_callback cli_commands_callbacks[N_CLI_COMMAND_CALLBACK];


char
parse_irc_packet(t_irc_client *irc_client,
                 t_packet *packet);

// cli_commands.c

char
on_server_cli_command(t_irc_client*, char*);

char
on_nick_cli_command(t_irc_client*, char*);

char
on_list_cli_command(t_irc_client*, char*);

char
on_join_cli_command(t_irc_client*, char*);

char
on_part_cli_command(t_irc_client*, char*);

char
on_users_cli_command(t_irc_client*, char*);

char
on_names_cli_command(t_irc_client*, char*);

char
on_msg_cli_command(t_irc_client*, char*);

char
on_accept_file_cli_command(t_irc_client*, char*);

char*
cmd_get_param(char *cmd, int p);

// commands.c

char
on_join_command(t_irc_client *client,
                t_packet *packet);

# define N_COMMAND_CALLBACK 14
typedef struct s_command_callback
{
    char *cmd;
    int code;
    char (*callback)(t_irc_client*, t_packet *);
    char flags;
} t_command_callback;
extern t_command_callback commands_callbacks[N_COMMAND_CALLBACK];

char
on_RPL_LISTSTART_command(t_irc_client *client,
                         t_packet *packet);

char
on_PING_command(t_irc_client *client,
                t_packet *packet);

char
on_JOIN_command(t_irc_client *client,
                t_packet *packet);
char
on_MODE_command(t_irc_client *client,
                t_packet *packet);
char
on_PRIVMSG_command(t_irc_client *client,
                   t_packet *packet);
char
on_RPL_CHANNELMODEIS_command(t_irc_client *client,
                             t_packet *packet);
char
on_RPL_LIST_command(t_irc_client *client,
                    t_packet *packet);
char
on_RPL_WHOREPLY_command(t_irc_client *client,
                        t_packet *packet);
char
on_RPL_NAMREPLY_command(t_irc_client *client,
                        t_packet *packet);
char
on_ERR_NICKNAMEINUSE_command(t_irc_client *client,
                             t_packet *packet);
char
on_PART_command(t_irc_client *client,
                t_packet *packet);
char
on_NICK_command(t_irc_client *client,
                t_packet *packet);
char
on_ERR_NOSUCHNICK_command(t_irc_client *client,
                          t_packet *packet);
char
on_welcome_command(t_irc_client *client,
                   t_packet *packet);

typedef struct s_irc_client
{
    t_my_select my_select;
    int fd;
    char logged;
    char *nickname;
    t_circular_buffer *cbuffer;
    t_channel *cur_channel;
    t_channels_list *registrated_channels;
} t_irc_client;

//channel.c

char
send_channel_msg(char *command,
                 t_irc_client *irc_client);

//cli.c

char*
cmd_get_param(char *cmd,
              int p);
char
parse_cli_command(char *command,
                  t_irc_client *irc_client);
char
on_cli_data(t_irc_client *irc_client);

// client.c

char
init_irc_client(t_irc_client *irc_client);

void
on_disconnect(t_irc_client *irc_client);

char
client_select_on_data(t_irc_client *irc_client);

char
on_network_data(t_irc_client *irc_client);

// select.c

int
my_select(t_my_select *ss,
          t_irc_client *irc_client);

#endif //PROJETS_CLIENT_H

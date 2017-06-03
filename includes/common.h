//
// Created by toune on 01/06/17.
//

#ifndef PROJETS_COMMON_H
#define PROJETS_COMMON_H

#include "cbuffer.h"
#include "util.h"
#include "socket.h"
#include "generic_list.h"

# define LISTEN_ADDRESS "0.0.0.0"
# define BUFFER_SIZE 512
# define IRC_PACKET_SIZE 512
# define IRC_CLIENT_MAX_CHANNELS 10
# define IRC_SERVER_MAX_CHANNELS 100
# define IRC_PACKET_NBR_PARAMS 15
# define IRC_CHANNEL_MAX_CLIENTS 100
# define IRC_SERVER_HOST "irc.lan"

# define FLAG_NONE 0
# define FLAG_LOG_FIRST 1

typedef t_generic_list t_channels_list;
typedef t_generic_list t_clients_list;

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

// packet.c
t_packet *init_packet(char *raw);
void free_packet(t_packet *packet);
void packet_set(t_packet *packet, char *cmd, char *content);
void packet_set_param(t_packet *packet, int i, char *param);
void packet_set_params(t_packet *packet, int nbr_params, ...);
char buffer_rm_crlf(char *buffer);
char send_reply_packet(int fd, t_packet *res);

char
*strdup_irc_packet(char *buffer);
char
simple_space_parser(t_packet *packet);

#endif //PROJETS_COMMON_H

/*
** packet_parser.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:03:25 2017 Thomas HENON
** Last update Sun May 28 00:03:26 2017 Thomas HENON
*/

#include <stdlib.h>
#include "myirc.h"

char
*packet_get_param(char *packet)
{
    strtok(packet, " ");
}

static char*
get_ptr_content(char *buffer)
{
    int i;

    i = -1;
    while (buffer[++i]) {
        if (buffer[i] == ' ' && buffer[i + 1] == ':') {
            return &buffer[i + 2];
        }
    }
    return NULL;
}

char
simple_space_parser(t_packet *packet)
{
    char *token;
    int i;
    char *buffer;
    char *tmp;

    buffer = strdup_irc_packet(packet->raw);
    tmp = buffer;
    buffer_rm_crlf(buffer);
    packet->content = NULL;
    i = -1;
    while ((token = strtok(buffer, " "))) {
        buffer = NULL;
        if (token[0] == ':') {
            packet->content = my_strdup(get_ptr_content(packet->raw));
            break;
        }
        if (++i == 0)
            packet->cmd = my_strdup(token);
        else {
            packet->params[i - 1] = my_strdup(token);
            packet->nbr_params++;
        }
    }
//    free(tmp);
    return 1;
}

char
*strdup_irc_packet(char *buffer)
{
    char *new_buffer;

    new_buffer = my_malloc(IRC_PACKET_SIZE);
    memcpy(new_buffer, buffer, IRC_PACKET_SIZE);
    return new_buffer;
}

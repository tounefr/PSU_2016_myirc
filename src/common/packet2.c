/*
** packet2.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Mon May 29 10:38:49 2017 Thomas HENON
** Last update Mon May 29 10:38:49 2017 Thomas HENON
*/

#include "server.h"

char
buffer_rm_crlf(char *buffer)
{
    int i;

    i = 0;
    while (buffer[i]) {
        if (buffer[i] == '\r' && buffer[i + 1] == '\n') {
            buffer[i] = '\0';
            buffer[i + 1] = '\0';
            return 1;
        }
        i++;
    }
    return 0;
}

# define FLAG_NONE 0
# define FLAG_APPND_SPACE 1
# define FLAG_APPND_COMMA 2

static void
cpy_buff(char *buffer,
         int *off,
         char *content,
         char flag)
{
    if (flag & FLAG_APPND_COMMA) {
        strcpy(&buffer[*off], ":");
        *off += 1;
    }
    strcpy(&buffer[*off], content);
    *off += strlen(content);
    if (flag & FLAG_APPND_SPACE) {
        strcpy(&buffer[*off], " ");
        *off += 1;
    }
}

char
send_reply_packet(int fd,
                  t_packet *res)
{
    char buffer[IRC_PACKET_SIZE + 1];
    int i;
    int i2;

    memset(&buffer, 0, IRC_PACKET_SIZE + 1);
    i = -1;
    i2 = 0;
    if (res->prefix) {
        buffer[i2++] = ':';
        cpy_buff(buffer, &i2, res->prefix, FLAG_APPND_SPACE);
    }
    cpy_buff(buffer, &i2, res->cmd, FLAG_APPND_SPACE);
    while (++i < IRC_PACKET_NBR_PARAMS && res->params[i])
        cpy_buff(buffer, &i2, res->params[i], FLAG_APPND_SPACE);
    if (res->content)
        cpy_buff(buffer, &i2, res->content, FLAG_APPND_COMMA);
    cpy_buff(buffer, &i2, "\r\n", FLAG_NONE);
    free_packet(res);
    printf("Send >> %s\n", buffer);
    return socket_send(&fd, buffer);
}

void
packet_set_params(t_packet *packet,
                  int nbr_params,
                  ...)
{
    int i;
    va_list args;

    va_start(args, nbr_params);
    i = -1;
    while (++i < nbr_params)
        packet->params[i] = va_arg(args, char*);
    va_end(args);
}
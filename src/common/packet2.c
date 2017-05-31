/*
** packet2.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Mon May 29 10:38:49 2017 Thomas HENON
** Last update Mon May 29 10:38:49 2017 Thomas HENON
*/

#include "myirc.h"

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

static void
cpy_buff(char *buffer, int *off, char *content, char flag)
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

void
packet_set_params(t_packet *packet, int nbr_params, ...)
{
    int i;
    va_list args;

    va_start(args, nbr_params);
    i = -1;
    while (++i < nbr_params)
        packet->params[i] = va_arg(args, char*);
    va_end(args);
}
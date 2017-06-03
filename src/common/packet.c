/*
** packet.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:03:16 2017 Thomas HENON
** Last update Sun May 28 00:03:17 2017 Thomas HENON
*/

#include "server.h"

t_packet
*init_packet(char *raw)
{
    t_packet *packet;
    int i;

    packet = my_malloc(sizeof(t_packet));
    packet->prefix = NULL;
    packet->raw = raw;
    i = -1;
    while (++i < IRC_PACKET_NBR_PARAMS)
        packet->params[i] = NULL;
    packet->content = NULL;
    packet->code = -1;
    packet->nbr_params = 0;
    return packet;
}

void
free_packet(t_packet *packet)
{
    int i;

    if (packet->cmd)
        free(packet->cmd);
    if (packet->raw)
        free(packet->raw);
    i = -1;
    while (++i < IRC_PACKET_NBR_PARAMS) {
        if (packet->params[i]) {
            free(packet->params[i]);
            packet->params[i] = NULL;
        }
    }
    if (packet->content)
        free(packet->content);
    free(packet);
}
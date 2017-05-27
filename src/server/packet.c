/*
** packet.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:03:16 2017 Thomas HENON
** Last update Sun May 28 00:03:17 2017 Thomas HENON
*/

#include <stdlib.h>
#include "myirc.h"

t_packet *init_packet(char *raw) {
    t_packet *packet;
    int i;

    packet = my_malloc(sizeof(t_packet));
    packet->raw = raw;
    i = -1;
    while (++i < IRC_PACKET_NBR_PARAMS)
        packet->params[i] = NULL;
    packet->content = NULL;
    packet->nbr_params = 0;
    return packet;
}

void free_packet(t_packet *packet) {
    int i;

    free(packet->cmd);
    i = -1;
    while (++i < IRC_PACKET_NBR_PARAMS) {
        if (packet->params[i]) {
            free(packet->params[i]);
            packet->params[i] = NULL;
        }
    }
    if (packet->content)
        free(packet->content);
    if (packet->raw)
        free(packet->raw);

}

char parse_irc_packet(t_irc_server *irc_server,
                      t_irc_client *irc_client,
                      t_packet *packet)
{
    int             i;
    char            *token;
    char            *buffer_tmp;

    buffer_tmp = strdup_irc_packet(packet->raw);
    while ((token = strtok(buffer_tmp, " "))) {
        buffer_tmp = NULL;
        if (token[0] == ':') {
            free(buffer_tmp);
            EXIT_ERROR(0, "Prefixes unsupported\n")
        }
        i = -1;
        while (++i < N_COMMAND_CALLBACK) {
            if (!strcmp(commands_callbacks[i].cmd, token)) {
                if (!commands_callbacks[i].parser(packet)) {
                    free(buffer_tmp);
                    EXIT_ERROR(0, "Failed to parse packet\n")
                }
                return commands_callbacks[i].callback(irc_server,
                                                      irc_client,
                                                      packet);
            }
        }
    }
    free(buffer_tmp);
    EXIT_ERROR(0, "Unknown packet\n")
}

char send_reply_packet(int fd, int code, char *buffer) {

}

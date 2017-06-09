/*
** client2.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc/src/server
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu Jun  8 18:09:30 2017 Thomas HENON
** Last update Thu Jun  8 18:09:30 2017 Thomas HENON
*/

#include "server.h"

char
on_client_data(t_irc_server *irc_server,
               t_client *irc_client)
{
    char        buffer[BUFFER_SIZE];
    int         readv;
    char        *raw;
    t_packet    *packet;

    if ((readv = read(irc_client->fd, buffer, BUFFER_SIZE)) <= 0) {
        on_exit_client(irc_server, irc_client);
        printf("client exit\n");
        return 0;
    }
    cbuffer_copy(irc_client->cbuffer, buffer, readv);
    while ((raw = cbuffer_extract(irc_client->cbuffer,
                                  IRC_PACKET_SIZE,
                                  "\r\n"))) {
        packet = init_packet(raw);
        printf("Recv << %s", raw);
        parse_irc_packet(irc_server, irc_client, packet);
        free_packet(packet);
    }
    return 1;
}

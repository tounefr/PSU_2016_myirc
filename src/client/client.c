/*
** client.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:01:02 2017 Thomas HENON
** Last update Sun Jun  4 12:01:02 2017 Thomas HENON
*/

#include "client.h"

char
init_irc_client(t_irc_client *irc_client)
{
    irc_client->registrated_channels = NULL;
    irc_client->cbuffer = cbuffer_new(IRC_PACKET_SIZE);
    irc_client->nickname = NULL;
    irc_client->logged = 0;
    irc_client->cur_channel = NULL;
    if (!socket_init(&irc_client->fd))
        return 0;
    return 1;
}

void
on_disconnect(t_irc_client *irc_client)
{
    printf("Disconnected\n");
    irc_client->logged = 0;
}

char
client_select_on_data(t_irc_client *irc_client)
{
    if (FD_ISSET(0, &irc_client->my_select.readfds))
        return on_cli_data(irc_client);
    else if (FD_ISSET(irc_client->fd,
                      &irc_client->my_select.readfds))
        return on_network_data(irc_client);
    return 0;
}

char
on_network_data(t_irc_client *irc_client)
{
    char        buffer[BUFFER_SIZE];
    int         readv;
    char        *raw;
    t_packet    *packet;
    char        returnv;

    if ((readv = read(irc_client->fd, buffer, BUFFER_SIZE)) <= 0) {
        on_disconnect(irc_client);
        return 1;
    }
    cbuffer_copy(irc_client->cbuffer, buffer, readv);
    //EXIT_ERROR(0, "cbuffer_extract failed\n")
    while ((raw = cbuffer_extract(irc_client->cbuffer,
                                  IRC_PACKET_SIZE,
                                  "\r\n"))) {
        packet = init_packet(raw);
        printf("Recv << %s", raw);
        returnv = parse_irc_packet(irc_client, packet);
        free_packet(packet);
    }
    return 1;
}

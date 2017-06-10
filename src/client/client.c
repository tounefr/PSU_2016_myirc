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
    irc_client->fd = -1;
    return 1;
}

char
on_disconnect(t_irc_client *irc_client)
{
    disp_message(INFO_LEVEL, "Disconnected");
    irc_client->logged = 0;
    return 1;
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
    char        buffer[IRC_PACKET_SIZE];
    int         readv;
    char        *raw;
    t_packet    *packet;

    memset(buffer, 0, sizeof(buffer));
    if ((readv = read(irc_client->fd, buffer,
                      irc_client->cbuffer->av_size)) <= 0)
        return on_disconnect(irc_client);
    cbuffer_copy(irc_client->cbuffer, buffer, readv);
    while ((raw = cbuffer_extract(irc_client->cbuffer,
                                  IRC_PACKET_SIZE,
                                  "\r\n"))) {
        packet = init_packet(raw);
        #ifdef DEBUG_MODE
        disp_message(DEBUG_LEVEL, "Recv << %s", raw);
        #endif
        if (!parse_irc_packet(irc_client, packet))
            disp_message(DEBUG_LEVEL, "Unknown packet << %s", raw);
        free_packet(packet);
    }
    return 1;
}

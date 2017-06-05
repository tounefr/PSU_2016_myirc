
#include "server.h"

char
on_client_data(t_irc_server *irc_server,
               t_client *irc_client)
{
    char        buffer[BUFFER_SIZE];
    int         readv;
    char        *raw;
    t_packet    *packet;
    char        returnv;

    if ((readv = read(irc_client->fd, buffer, BUFFER_SIZE)) <= 0) {
        on_exit_client(irc_server, irc_client);
        printf("client exit\n");
        return 0;
    }
    cbuffer_copy(irc_client->cbuffer, buffer, readv);
    //EXIT_ERROR(0, "cbuffer_extract failed\n")
    while ((raw = cbuffer_extract(irc_client->cbuffer,
                                  IRC_PACKET_SIZE,
                                  "\r\n"))) {
        packet = init_packet(raw);
        printf("Recv << %s", raw);
        returnv = parse_irc_packet(irc_server, irc_client, packet);
        free_packet(packet);
    }
    return 1;
}
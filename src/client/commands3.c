
#include "client.h"

char
on_NICK_command(t_irc_client *client,
                t_packet *packet)
{
    char *nick_src;

    nick_src = parse_packet_prefix_dst(packet);
    if (client->nickname && strcmp(nick_src, client->nickname)) {
        disp_message(INFO_LEVEL, "%s s'appelle maintenant %s",
            nick_src, packet->content);
        return 1;
    }
    client->nickname = my_strdup(packet->content);
    disp_message(INFO_LEVEL, "Vous vous appelez maintenant : '%s'",
                 client->nickname);
}

char
on_ERR_NOSUCHNICK_command(t_irc_client *client,
                          t_packet *packet)
{

}

char
on_welcome_command(t_irc_client *client,
                   t_packet *packet)
{
    if (!packet->content)
        return 1;
    disp_message(INFO_LEVEL, "%s", packet->content);
}

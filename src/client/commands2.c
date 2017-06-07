
#include "client.h"

char
on_RPL_LIST_command(t_irc_client *client,
                    t_packet *packet)
{

}

char
on_RPL_WHOREPLY_command(t_irc_client *client,
                        t_packet *packet)
{

}

char
on_RPL_NAMREPLY_command(t_irc_client *client,
                        t_packet *packet)
{

}

char
on_ERR_NICKNAMEINUSE_command(t_irc_client *client,
                             t_packet *packet)
{
    disp_message(WARN_LEVEL, "Ce pseudo est déjà utilisé !");
}

char
on_PART_command(t_irc_client *client,
                t_packet *packet)
{
    char *nick_src;
    char *channel_name;

    printf("on_PART_command\n");
    if (!packet->prefix || !packet->params[0])
        return 0;
    if (!(channel_name = normalize_channel_name(packet->params[0])))
        return 0;
    nick_src = parse_packet_prefix_dst(packet);
    if (!strcmp(nick_src, client->nickname)) {
        disp_message(INFO_LEVEL, "Vous avez quitté le channel #%s",
                     channel_name);
        client->cur_channel = NULL;
        return 1;
    }
    disp_message(INFO_LEVEL, "%s a quitté le channel #%s",
                 nick_src, channel_name);
    //TODO: free channel
    client->cur_channel = NULL;
}
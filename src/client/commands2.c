
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
    char *channel_name;

    if (!packet->params[0] || !packet->params[1] ||
            !packet->params[2] || !packet->content)
        return 0;
    if (!(channel_name = normalize_channel_name(packet->params[2])))
        return 0;
    return disp_message(INFO_LEVEL, "[Users #%s]\n%s\n",
                        channel_name, packet->content);
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
    t_channel *channel;

    if (!packet->prefix || !packet->params[0])
        return 0;
    if (!(channel_name = normalize_channel_name(packet->params[0])))
        return 0;
    nick_src = parse_packet_prefix_dst(packet);
    if (!strcmp(nick_src, client->nickname)) {
        if (!(channel = irc_channel_exists(client->registrated_channels,
                                           channel_name)))
            return 0;
        generic_list_remove(&client->registrated_channels,
                            channel, NULL);
        if (channel == client->cur_channel)
            client->cur_channel = NULL;
        disp_message(INFO_LEVEL, "Vous avez quitté le channel #%s",
                     channel_name);
        return 1;
    }
    disp_message(INFO_LEVEL, "%s a quitté le channel #%s",
                 nick_src, channel_name);

}

#include "client.h"

char
on_users_cli_command(t_irc_client *irc_client,
                     char *cmd)
{
    return dprintf(irc_client->fd, "WHO *\r\n");
}

char
on_names_cli_command(t_irc_client *irc_client,
                     char *cmd)
{
    char *channel_name;

    if (!(channel_name = cmd_get_param(cmd, 1)) ||
            !(channel_name = normalize_channel_name(channel_name)))
        return disp_message(ERR_LEVEL, "Wrong usage");
    return dprintf(irc_client->fd, "NAMES #%s\r\n", channel_name);
}

char
on_msg_cli_command(t_irc_client *irc_client,
                   char *cmd)
{
    char *nick_dst;
    char *msg;
    char *content;

    if (!(nick_dst = cmd_get_param(cmd, 1)) ||
            !(content = cmd_get_content_at(cmd, 2)))
        return disp_message(ERR_LEVEL, "Wrong usage");
    return dprintf(irc_client->fd, "PRIVMSG %s :%s\r\n",
                   nick_dst, content);
}

char
on_accept_file_cli_command(t_irc_client *irc_client,
                           char *cmd)
{

}

char
on_part_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *channel_name;
    t_channel *channel;

    if (!(channel_name = cmd_get_param(cmd, 1)))
        return disp_message(ERR_LEVEL, "Wrong usage");
    if (!(channel_name = normalize_channel_name(channel_name)))
        return disp_message(ERR_LEVEL, "Failed to get channel name");

    if (!(channel = irc_channel_exists(irc_client->registrated_channels,
                                       channel_name)))
        return disp_message(ERR_LEVEL,
                            "Vous n'êtes pas connecté à ce channel");
    return dprintf(irc_client->fd, "PART #%s\r\n",
                   irc_client->cur_channel->name);
}
/*
** commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:01:08 2017 Thomas HENON
** Last update Sun Jun  4 12:01:09 2017 Thomas HENON
*/

#include "client.h"

t_command_callback commands_callbacks[N_COMMAND_CALLBACK] =
{
    { NULL, 001, on_welcome_command, FLAG_NONE },
    { "PART", -1, on_PART_command, FLAG_NONE },
    { "NICK", -1, on_NICK_command, FLAG_NONE },
    { "MODE", -1, on_MODE_command, FLAG_NONE },
    { "JOIN", -1, on_JOIN_command, FLAG_NONE },
    { "PING", -1, on_PING_command, FLAG_NONE },
    { "PRIVMSG", -1, on_PRIVMSG_command, FLAG_NONE },
    { "RPL_CHANNELMODEIS", 324, on_RPL_CHANNELMODEIS_command, FLAG_NONE },
    { "RPL_LIST", 322, on_RPL_LIST_command, FLAG_NONE },
    { "RPL_WHOREPLY", 352, on_RPL_WHOREPLY_command, FLAG_NONE },
    { "RPL_NAMREPLY", 353, on_RPL_NAMREPLY_command, FLAG_NONE },
    { "RPL_LISTSTART", 321, on_RPL_LISTSTART_command, FLAG_NONE },
    { "ERR_NICKNAMEINUSE", 433, on_ERR_NICKNAMEINUSE_command, FLAG_NONE },
    { "ERR_NOSUCHNICK", 403, on_ERR_NOSUCHNICK_command, FLAG_NONE }
};

char
on_PING_command(t_irc_client *client,
                t_packet *packet)
{
    if (!packet->content)
        return 0;
    dprintf(client->fd, "PONG :%s\r\n", packet->content);
}

char
on_JOIN_command(t_irc_client *client,
                t_packet *packet)
{
    char *channel_name;
    char *nick_dst;

    if ((!packet->params[0] && !packet->content) ||
            !packet->prefix || !client->nickname)
        return 0;
    channel_name = packet->params[0] ? packet->params[0] : packet->content;
    if (!(channel_name = normalize_channel_name(channel_name)))
        return 0;
    nick_dst = parse_packet_prefix_dst(packet);
    if (!strcmp(nick_dst, client->nickname))
        client->cur_channel = new_irc_channel(&client->registrated_channels,
                                          channel_name);
    generic_list_append(&client->registrated_channels, client->cur_channel);
    return disp_channel_message("", channel_name,
                                "%s a joint le channel #%s\n",
                                nick_dst, channel_name);
}

char
on_MODE_command(t_irc_client *client,
                t_packet *packet)
{

}

char
on_PRIVMSG_command(t_irc_client *client,
                   t_packet *packet)
{
    char *nick_src;
    char *channel_name;

    if (!packet->prefix || !packet->params[0] || !packet->content)
        return 0;
    nick_src = parse_packet_prefix_dst(packet);
    if (packet->params[0][0] == '#') {
        if (!(channel_name = normalize_channel_name(packet->params[0])))
            return 0;
        return disp_channel_message(nick_src, channel_name, packet->content);
    }
    return disp_privmsg_message(nick_src, packet->content);
}

char
on_RPL_CHANNELMODEIS_command(t_irc_client *client,
                             t_packet *packet)
{

}
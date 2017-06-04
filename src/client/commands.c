/*
** commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:01:08 2017 Thomas HENON
** Last update Sun Jun  4 12:01:09 2017 Thomas HENON
*/

#include <time.h>
#include "client.h"

t_command_callback commands_callbacks[N_COMMAND_CALLBACK] =
{
    { NULL, 001, on_welcome_command, FLAG_NONE },
    { "PART", -1, on_PART_command, FLAG_NONE },
    { "NICK", -1, on_NICK_command, FLAG_NONE },
    { "MODE", -1, on_MODE_command, FLAG_NONE },
    { "JOIN", -1, on_JOIN_command, FLAG_NONE },
    { "PRIVMSG", -1, on_PRIVMSG_command, FLAG_NONE },
    { "RPL_CHANNELMODEIS", 324, on_RPL_CHANNELMODEIS_command, FLAG_NONE },
    { "RPL_LIST", 322, on_RPL_LIST_command, FLAG_NONE },
    { "RPL_WHOREPLY", 352, on_RPL_WHOREPLY_command, FLAG_NONE },
    { "RPL_NAMREPLY", 353, on_RPL_NAMREPLY_command, FLAG_NONE },
    { "ERR_NICKNAMEINUSE", 433, on_ERR_NICKNAMEINUSE_command, FLAG_NONE },
    { "ERR_NOSUCHNICK", 403, on_ERR_NOSUCHNICK_command, FLAG_NONE }
};

char
on_JOIN_command(t_irc_client *client,
                t_packet *packet)
{
    char *channel_name;
    char *nick_dst;

    if (!packet->params[0] || !packet->prefix)
        return 0;
    if (!(channel_name = normalize_channel_name(packet->params[0])))
        return 0;
    nick_dst = parse_packet_prefix_dst(packet);
    if (!client->cur_channel && !strcmp(nick_dst, client->nickname))
        client->cur_channel = new_irc_channel(&client->registrated_channels,
                                          channel_name);
    printf("%s a joint le channel\n", nick_dst);
    return 1;
}

char
on_MODE_command(t_irc_client *client,
                t_packet *packet)
{

}

char*
get_prompt_date()
{
    time_t rawtime;
    struct tm *info;
    char *date_buffer;

    time(&rawtime);
    info = localtime(&rawtime);
    strftime(date_buffer, 80, "%d/%m/%Y %H:%M", info);
    return date_buffer;
}

char
on_PRIVMSG_command(t_irc_client *client,
                   t_packet *packet)
{
    char *nick_src;
    char *channel_name;

    if (!packet->prefix || !packet->params[0] || !packet->content)
        return 0;
    if (!(channel_name = normalize_channel_name(packet->params[0])))
        return 0;
    nick_src = parse_packet_prefix_dst(packet);
    printf("%s [#%s] <%s>: %s\n",
           get_prompt_date(),
           channel_name, nick_src, packet->content);
}

char
on_RPL_CHANNELMODEIS_command(t_irc_client *client,
                             t_packet *packet)
{

}

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
    printf("Ce pseudo est déjà utilisé !\n");
}

char
on_PART_command(t_irc_client *client,
                t_packet *packet)
{

}

char
on_NICK_command(t_irc_client *client,
                t_packet *packet)
{
    client->nickname = my_strdup(packet->content);
    printf("Vous vous appelez maintenant : '%s'\n",
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
    printf("%s\n", packet->content);
}

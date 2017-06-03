
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

}

/*
** cli_commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:00:56 2017 Thomas HENON
** Last update Sun Jun  4 12:00:57 2017 Thomas HENON
*/

#include "client.h"

t_cli_command_callback cli_commands_callbacks[N_CLI_COMMAND_CALLBACK] =
{
    { "server", on_server_cli_command, FLAG_NONE },
    { "nick", on_nick_cli_command, FLAG_LOG_FIRST },
    { "list", on_list_cli_command, FLAG_LOG_FIRST },
    { "join", on_join_cli_command, FLAG_LOG_FIRST },
    { "part", on_part_cli_command, FLAG_LOG_FIRST },
    { "users", on_users_cli_command, FLAG_LOG_FIRST },
    { "names", on_names_cli_command, FLAG_LOG_FIRST },
    { "msg", on_msg_cli_command, FLAG_LOG_FIRST },
    { "accept_file", on_accept_file_cli_command, FLAG_LOG_FIRST },
    { "channel", on_channel_cli_command, FLAG_LOG_FIRST },
    { "help", on_help_cli_command, FLAG_NONE },
};

void
identify_me(t_irc_client *irc_client,
            char *nickname)
{
    dprintf(irc_client->fd, "NICK %s\r\n", nickname);
    dprintf(irc_client->fd, "USER %s %s %s :%s\r\n",
            nickname, nickname,
            "127.0.0.1", nickname);
    irc_client->nickname = my_strdup(nickname);
}

char
on_channel_cli_command(t_irc_client *irc_client,
                      char *cmd)
{
    char *channel_name;
    t_channel *channel;

    if (!(channel_name = cmd_get_param(cmd, 1)) ||
            !(channel_name = normalize_channel_name(channel_name)))
        return !disp_message(ERR_LEVEL, "Wrong usage");
    if (!(channel = irc_channel_exists(irc_client->registrated_channels,
                                 channel_name)))
        return disp_message(ERR_LEVEL,
                            "Vous n'êtes pas connecté à ce channel !");
    irc_client->cur_channel = channel;
    return 1;
}

char
on_nick_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *nickname;

    if (!(nickname = cmd_get_param(cmd, 1)))
        return disp_message(ERR_LEVEL, "Wrong usage");
    return dprintf(irc_client->fd, "NICK %s\r\n", nickname);
}

char
on_list_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *channel_name;

    if ((channel_name = cmd_get_param(cmd, 1))) {
        if (!(channel_name = normalize_channel_name(channel_name)))
            return disp_message(ERR_LEVEL, "Failed to get channel name");
        return dprintf(irc_client->fd, "LIST #%s\r\n", channel_name);
    }
    else
        return dprintf(irc_client->fd, "LIST\r\n");
}

char
on_join_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    char *channel_name;
    t_channel *channel;

    (void)channel;
    if (!(channel_name = cmd_get_param(cmd, 1)))
        return disp_message(ERR_LEVEL, "Wrong usage");
    if (!(channel_name = normalize_channel_name(channel_name)))
        return disp_message(ERR_LEVEL, "Failed to get channel name");
    if (irc_channel_exists(irc_client->registrated_channels, channel_name))
        return disp_message(INFO_LEVEL, "Vous êtes déjà connecté à ce channel");
    return dprintf(irc_client->fd, "JOIN #%s\r\n", channel_name);
}
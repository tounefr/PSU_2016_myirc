/*
** channel.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:00:39 2017 Thomas HENON
** Last update Sun Jun  4 12:00:40 2017 Thomas HENON
*/

#include "client.h"

char*
normalize_message(char *message)
{
    int i;
    int len;

    len = strlen(message);
    for (i = 0; i < len; i++) {
        if (message[i] == '\n')
            message[i] = '\0';
    }
    return message;
}

char
send_channel_msg(char *command,
                 t_irc_client *irc_client)
{
    char *message;

    if (!irc_client->logged)
        return disp_message(WARN_LEVEL, "Log first");
    else if (!irc_client->cur_channel)
        return disp_message(WARN_LEVEL, "Join a channel first");
    message = normalize_message(command);
    disp_channel_message(irc_client->nickname,
                         irc_client->cur_channel->name,
                         message);
    return dprintf(irc_client->fd, "PRIVMSG #%s :%s\r\n",
        irc_client->cur_channel->name, message);
}
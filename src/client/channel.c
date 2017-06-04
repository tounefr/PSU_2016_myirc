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

char
send_channel_msg(char *command,
                 t_irc_client *irc_client)
{
    char *message;

    if (!irc_client->logged)
        return !printf("Log first\n");
    else if (!irc_client->cur_channel)
        return !printf("Join a channel first\n");
    message = command;
    return dprintf(irc_client->fd, "PRIVMSG #%s :%s\r\n",
        irc_client->cur_channel->name, message);
}

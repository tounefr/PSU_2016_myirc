/*
** channel2.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:02:43 2017 Thomas HENON
** Last update Sun Jun  4 12:02:44 2017 Thomas HENON
*/

#include "server.h"

char
free_channel(void *data)
{
    t_channel *irc_channel;
    t_client *client;

    if (!data)
        return 0;
    irc_channel = (t_channel*)data;
    if (irc_channel->name)
        free(irc_channel->name);
    if (irc_channel->topic)
        free(irc_channel->topic);
    free(irc_channel);
    return 1;
}

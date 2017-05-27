/*
** channel_commands.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:06:38 2017 Thomas HENON
** Last update Sun May 28 00:06:39 2017 Thomas HENON
*/

#include <string.h>
#include "myirc.h"

char                check_pseudo_already_used(t_irc_server *irc_server,
                                              char *pseudo)
{
    t_irc_client    *clients;

    clients = irc_server->irc_clients;
    while (clients) {
        if (clients->pseudo &&
                !strcmp(clients->pseudo, pseudo))
            return 1;
        clients = clients->next;
    }
    return 0;
}
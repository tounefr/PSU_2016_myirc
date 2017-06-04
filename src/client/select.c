/*
** select.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:01:28 2017 Thomas HENON
** Last update Sun Jun  4 12:01:29 2017 Thomas HENON
*/

#include "client.h"

int
my_select(t_my_select *ss,
          t_irc_client *irc_client)
{
    init_my_select(ss);
    add_readfd_my_select(ss, 0);
    ss->nfds = 1;
    if (irc_client->fd != -1 && irc_client->logged) {
        add_readfd_my_select(ss, irc_client->fd);
        ss->nfds++;
    }
    return select(ss->nfds, &ss->readfds,
                  &ss->writefds, &ss->exceptfds,
                  &ss->timeout);
}

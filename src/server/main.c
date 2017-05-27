/*
** main.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:18:12 2017 Thomas HENON
** Last update Sat May 27 20:18:12 2017 Thomas HENON
*/

#include <stdlib.h>
#include "myirc.h"

static char usage(char *bin)
{
    fprintf(stderr, "Usage: %s --help\n", bin);
    return 1;
}

int                 main(int ac, char **av)
{
    t_irc_server    irc_server;

    if (ac != 2 || !is_number(av[1]))
        return usage(av[0]);
    irc_server.listen_address = LISTEN_ADDRESS;
    irc_server.listen_port = atoi(av[1]);
    irc_server.irc_clients = NULL;
    return ((start_irc_server(&irc_server)) ? 0 : 84);
}

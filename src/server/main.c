/*
** main.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:18:12 2017 Thomas HENON
** Last update Sat May 27 20:18:12 2017 Thomas HENON
*/

#include "server.h"

static char
usage(char *bin)
{
    fprintf(stderr, "Usage: %s port\n", bin);
    return 84;
}

static void disp_headers()
{
    printf("\n"
       "   __  ___     _______  _____        ____                    \n"
       "  /  |/  __ __/  _/ _ \\/ ___/ ____  / _____ _____  _____ ____\n"
       " / /|_/ / // _/ // , _/ /__  /___/ _\\ \\/ -_/ __| |/ / -_/ __/\n"
       "/_/  /_/\\_, /___/_/|_|\\___/       /___/\\__/_/  |___/\\__/_/   \n"
       "       /___/                                                 \n\n");
    printf("A very basic IRC server by thomas.henon@epitech.eu"
                   " & valentin.strassel@epitech.eu\n\n");
}

void
sigint_handler(int signum)
{
    t_irc_server *irc_server;

    if (signum != SIGINT)
        return;
    irc_server = get_irc_server();
    generic_list_destory(&irc_server->channels, free_channel);
    generic_list_destory(&irc_server->irc_clients, free_irc_client);
    exit(0);
}

t_irc_server
*get_irc_server()
{
    static t_irc_server irc_server;
    return &irc_server;
}

int
main(int ac, char **av)
{
    t_irc_server *irc_server;

    if (ac != 2 || !is_number(av[1]))
        return usage(av[0]);
    disp_headers();
    irc_server = get_irc_server();
    irc_server->listen_address = LISTEN_ADDRESS;
    irc_server->listen_port = atoi(av[1]);
    signal(SIGINT, sigint_handler);
    if (!init_irc_server(irc_server))
        return 84;
    return ((start_irc_server(irc_server)) ? 0 : 84);
}

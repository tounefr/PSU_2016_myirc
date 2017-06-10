/*
** main.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:16:59 2017 Thomas HENON
** Last update Sat May 27 20:16:59 2017 Thomas HENON
*/

#include "client.h"

t_irc_client *
get_irc_client()
{
    static t_irc_client irc_client;
    return &irc_client;
}

void
sigint_handler(int signum)
{
    if (signum != SIGINT)
        return;
    exit(1);
}

static void disp_headers()
{
    printf("[MYIRC-Client]\n");
    printf("A very basic IRC client by thomas.henon@epitech.eu"
                   " & valentin.strassel@epitech.eu\n\n"
                   "Type /help to list the available commands\n\n");
}

char
start_irc_client()
{
    t_irc_client *irc_client;
    int retrv;

    disp_headers();
    irc_client = get_irc_client();
    if (!init_irc_client(irc_client))
        return 0;
    while (1) {
        retrv = my_select(&irc_client->my_select, irc_client);
        if (retrv == -1)
            return exit_error(0, "select error : %s\n", strerror(errno));
        else if (retrv != 0 && !client_select_on_data(irc_client))
            return 0;
    }
    return 1;
}

int
main() {
    signal(SIGINT, sigint_handler);
    return (start_irc_client() ? 0 : 84);
}
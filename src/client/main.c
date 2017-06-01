/*
** main.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:16:59 2017 Thomas HENON
** Last update Sat May 27 20:16:59 2017 Thomas HENON
*/

#include <signal.h>
#include <stdlib.h>
#include "client.h"

void
sigint_handler(int signum)
{
    if (signum != SIGINT)
        return;

    exit(1);
}

char
start_irc_client()
{
    t_my_select my_select;

    return 1;
}

int main() {
    signal(SIGINT, sigint_handler);
    return !start_irc_client();
}

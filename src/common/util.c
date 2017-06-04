/*
** util.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:17:15 2017 Thomas HENON
** Last update Sat May 27 20:17:15 2017 Thomas HENON
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "util.h"

char
is_number(char *str)
{
    if (strlen(str) == 0)
        return 0;
    while (*str) {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

void
*my_malloc(size_t size)
{
    void    *ptr;

    if (!(ptr = calloc(1, size))) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    return ptr;
}

int
nbr_chars_in_str(char *str,
                 char c)
{
    int i;
    int n;

    n = 0;
    i = -1;
    while (str[++i]) {
        if (str[i] == c)
            n++;
    }
    return n;
}

char
*my_strdup(char *str)
{
    if (!(str = strdup(str)))
        malloc_error();
    return str;
}

char*
normalize_channel_name(char *channel)
{
    int i;

    if (!channel)
        return NULL;
    if (channel[0] == '&' || channel[0] == '#')
        channel++;
    if (strlen(channel) > 200)
        return exit_ptr_error(0, "channel name > 200\n");
    i = -1;
    while (channel[++i]) {
        if (channel[i] < 0 || channel[i] > 255 ||
            channel[i] == 7 || channel[i] == ' ')
            return exit_ptr_error(NULL, "wrong channel name\n");
    }
    channel = my_strdup(channel);
    return channel;
}

char*
generate_nickname()
{
    static char init_srand = 0;
    char *nickname;
    int rand_num;

    if (!init_srand) {
        srand(time(NULL));
        init_srand = 1;
    }
    nickname = my_malloc(100);
    rand_num = rand() % 10001;
    snprintf(nickname, 99, "Guest%d", rand_num);
    return nickname;
}
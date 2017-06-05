/*
** channel2.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:02:43 2017 Thomas HENON
** Last update Sun Jun  4 12:02:44 2017 Thomas HENON
*/

#include <time.h>
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
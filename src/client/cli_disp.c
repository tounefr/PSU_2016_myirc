/*
** cli_disp.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc/src/client
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Thu Jun  8 18:08:26 2017 Thomas HENON
** Last update Thu Jun  8 18:08:27 2017 Thomas HENON
*/

#include "client.h"

char*
get_prompt_date()
{
    time_t rawtime;
    struct tm *info;
    char *date_buffer;

    date_buffer = my_malloc(100);
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(date_buffer, 99, "%d/%m/%Y %H:%M", info);
    return date_buffer;
}

char
disp_channel_message(char *pseudo,
                     char *channel,
                     char *message,
                     ...)
{
    char *date_prompt;
    va_list args;

    va_start(args, message);
    date_prompt = get_prompt_date();
    printf("%s [#%s] <%s>: ", date_prompt, channel, pseudo);
    vprintf(message, args);
    va_end(args);
    printf("\n");
    free(date_prompt);
    return 1;
}

char
disp_privmsg_message(char *pseudo,
                     char *message,
                    ...)
{
    char *date_prompt;
    va_list args;

    va_start(args, message);
    date_prompt = get_prompt_date();
    printf("%s <%s>: ",
           date_prompt, pseudo);
    vprintf(message, args);
    va_end(args);
    printf("\n");
    free(date_prompt);
    return 1;
}

char
disp_announce_message(char *message,
                      ...)
{
    char *date_prompt;
    va_list args;

    va_start(args, message);
    date_prompt = get_prompt_date();
    printf("%s [ANNOUNCE]: ",
           date_prompt);
    vprintf(message, args);
    va_end(args);
    printf("\n");
    free(date_prompt);
    return 1;
}

char
disp_message(char type,
             const char *message,
             ...)
{
    va_list args;

    (void)type;
    va_start(args, message);
    vprintf(message, args);
    printf("\n");
    va_end(args);
    return 1;
}

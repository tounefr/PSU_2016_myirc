/*
** cli_commands3.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat Jun 10 12:47:11 2017 Thomas HENON
** Last update Sat Jun 10 12:47:13 2017 Thomas HENON
*/

#include "client.h"

char
on_help_cli_command(t_irc_client *irc_client,
                    char *cmd)
{
    (void)irc_client;
    (void)cmd;
    disp_message(INFO_LEVEL,
     "\n[HELP]\n"
     "/server $host[:$port]: ""connects to a server\n"
         "/nick $nickname: defines the user’s nickname in the server\n"
         "/list [$string]: lists the server’s available channels.\n"
         "\tOnly display the channels that "
         "contain the $string string (when specified)\n"
         "/join $channel: joins a server’s channel\n"
         "/part $channel: leaves a channel\n"
         "/users: lists the nicknames of "
         "the users that are connected to the server\n"
         "/names $channel: lists the nicknames"
         " of the users connected to the channel\n"
         "$message: sends a message to all"
         " of the users that are connected to the channel\n"
         "/msg $nickname $message:" "sends a message to a specific user\n"
         "/msg $channel $nickname $file:" "sends a file to a user\n"
         "/channel $channelchange the current channel\n"
         "/accept file $nickname:"
         "accepts the reception of a file coming from one of the channel’s\n"
             "users\n");
    return 1;
}

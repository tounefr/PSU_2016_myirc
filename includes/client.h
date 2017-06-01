
#ifndef PROJETS_CLIENT_H
#define PROJETS_CLIENT_H

#include "common.h"

# define N_CLI_COMMAND_CALLBACK 9
typedef struct s_cli_command_callback
{
    char *cmd;
    char (*callback)();
    char flags;
} t_cli_command_callback;

char
on_server_command();

char
on_nick_command();

char
on_list_command();

char
on_join_command();

char
on_part_command();

char
on_users_command();

char
on_names_command();

char
on_msg_command();

char
on_accept_file_command();

typedef struct s_channel
{

} t_channel;

typedef struct s_irc_client
{

} t_irc_client;

#endif //PROJETS_CLIENT_H

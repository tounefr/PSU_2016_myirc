
#include "client.h"

t_cli_command_callback cli_commands_callbacks[N_CLI_COMMAND_CALLBACK] =
{
        { "server", on_server_command, 0 },
        { "nick", on_nick_command, 0 },
        { "list", on_list_command, 0 },
        { "join", on_join_command, 0 },
        { "part", on_part_command, 0 },
        { "users", on_users_command, 0 },
        { "names", on_names_command, 0 },
        { "msg", on_msg_command, 0 },
        { "accept_file", on_accept_file_command, 0 }
};

char
on_server_command()
{

}

char
on_nick_command()
{

}

char
on_list_command()
{

}

char
on_join_command()
{

}

char
on_part_command()
{

}

char
on_users_command()
{

}

char
on_names_command()
{

}

char
on_msg_command()
{

}

char
on_accept_file_command()
{

}
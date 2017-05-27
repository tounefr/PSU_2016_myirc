
#include "myirc.h"

t_command_callback commands_callbacks[10] =
{
        { "JOIN", NULL }, // /join
        { "LIST", NULL }, // /list
        { "NICK", NULL }, // /nick
        { "PART", NULL }, // /part
        { "WHO", NULL }, // /users
        { "NAMES", NULL }, // /names
        { "PRIVMSG", NULL }
};
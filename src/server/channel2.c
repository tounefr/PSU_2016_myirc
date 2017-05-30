
#include <stdlib.h>
#include "myirc.h"

char
free_irc_channel(void *data)
{
    t_irc_channel *irc_channel;
    t_irc_client *client;

    if (!data)
        return 0;
    irc_channel = (t_irc_channel*)data;
    if (irc_channel->name)
        free(irc_channel->name);
    if (irc_channel->topic)
        free(irc_channel->topic);
    free(irc_channel);
    return 1;
}

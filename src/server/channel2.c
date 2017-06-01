
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

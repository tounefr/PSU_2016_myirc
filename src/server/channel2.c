
#include <stdlib.h>
#include "myirc.h"

void
free_irc_channel(t_irc_channel *irc_channel)
{
    if (irc_channel->name)
        free(irc_channel->name);
    if (irc_channel->topic)
        free(irc_channel->topic);
    //TODO: free clients
    free(irc_channel);
}


#include "myirc.h"
#include "util.h"

t_irc_channel       *init_irc_channel(char *name) {
    t_irc_channel   *irc_channel;

    irc_channel = my_malloc(sizeof(t_irc_channel));
    if (!(irc_channel->name = strdup(name)))
        malloc_error();
    irc_channel->max_clients = IRC_CHANNEL_MAX_CLIENTS;
    irc_channel->clients = NULL;
    irc_channel->op = NULL;
    return irc_channel;
}

void free_irc_channel(t_irc_channel *irc_channel) {

}
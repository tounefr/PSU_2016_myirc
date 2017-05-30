
#include <stdlib.h>
#include "myirc.h"

char
free_irc_channel(void *data)
{
    t_irc_channel *irc_channel;
    t_irc_client *client;
    t_clients_list *clients;
    t_irc_server *irc_server;

    irc_server = get_irc_server();
    clients = data;
    if (irc_channel->name)
        free(irc_channel->name);
    if (irc_channel->topic)
        free(irc_channel->topic);
    generic_list_remove(&irc_server->channels, irc_channel);
    clients = irc_server->irc_clients;
    while ((client = generic_list_foreach(clients))) {
        clients = NULL;
        generic_list_remove(&client->registred_channels, irc_channel);
    }
    //TODO: free clients
    free(irc_channel);
}

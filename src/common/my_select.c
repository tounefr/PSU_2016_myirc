
#include "common.h"

void
init_my_select(t_my_select *server_select)
{
    server_select->timeout.tv_sec = 0;
    server_select->timeout.tv_usec = 5000;
    server_select->nfds = -1;
    server_select->readfds_n = 0;
    server_select->writefds_n = 0;
    FD_ZERO(&server_select->readfds);
    FD_ZERO(&server_select->writefds);
}

void
add_readfd_my_select(t_my_select *server_select,
                         int fd)
{
    FD_SET(fd, &server_select->readfds);
    if (fd > server_select->nfds)
        server_select->nfds = fd + 1;
    server_select->readfds_n++;
}


#include <stdlib.h>
#include "myirc.h"

char
*cbuffer_extract(t_circular_buffer *cbuffer,
                 int packet_size,
                 char *delim)
{
    int     cur;
    int     end;
    int     start;
    char    *packet;
    int     packet_i;

    packet_i = 0;
    packet = my_malloc(packet_size);
    start = cbuffer->cur_off;
    cur = start;
    end = cur + cbuffer->size;
    while (cur < end - 1) {
        packet[packet_i++] = cbuffer_get_char_at(cbuffer, cur);
        cbuffer_set_char_at(cbuffer, packet_i - 1, '\0');
        if (packet_i >= 2 &&
            (packet[packet_i - 2] == '\r' &&
             packet[packet_i - 1] == '\n')) {
            cbuffer->cur_off = (cur + 1) % cbuffer->size;
            return packet;
        }
        cur++;
    }
    free(packet);
    return NULL;
}

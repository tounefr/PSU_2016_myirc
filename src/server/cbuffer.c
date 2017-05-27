
#include <stdlib.h>
#include "myirc.h"

t_circular_buffer       *cbuffer_new(int size)
{
    t_circular_buffer   *cbuffer;

    cbuffer = my_malloc(sizeof(t_circular_buffer));
    cbuffer->size = size;
    cbuffer->cur_off = 0;
    cbuffer->buffer = my_malloc(size);
    return cbuffer;
}

void    cbuffer_debug(t_circular_buffer *cbuffer)
{
    int i;

    i = -1;
    printf("off : %d\n", cbuffer->cur_off);
    printf("Buffer : \n");
    printf("%s", cbuffer->buffer);
    while (++i < cbuffer->size) {
        printf("%d ", cbuffer->buffer[i]);
    }
    printf("\n");
}

char cbuffer_get_char_at(t_circular_buffer *cbuffer, int i)
{
    return cbuffer->buffer[i % cbuffer->size];
}

void    cbuffer_copy(t_circular_buffer *cbuffer,
                     char *buff,
                     int buff_size)
{
    int i;
    int i2;

    i = 0;
    i2 = cbuffer->cur_off;
    while (buff_size >= 0) {
        if (cbuffer->cur_off >= cbuffer->size)
            cbuffer->cur_off = 0;
        cbuffer->buffer[i2++] = buff[i++];
        buff_size--;
    }
}

char        *cbuffer_extract(t_circular_buffer *cbuffer,
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
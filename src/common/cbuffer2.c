/*
** cbuffer2.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun Jun  4 12:01:45 2017 Thomas HENON
** Last update Sun Jun  4 12:01:46 2017 Thomas HENON
*/

#include "util.h"
#include "cbuffer.h"

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

void
cbuffer_copy(t_circular_buffer *cbuffer,
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
//        cbuffer_set_char_at(cbuffer->buffer, i2++, buff[i++]);
        buff_size--;
    }
}

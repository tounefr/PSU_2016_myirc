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
    int i;
    char *packet;
    char c1;
    char c2;

    (void)delim;
    packet = my_malloc(packet_size);
    i = -1;
    while (++i < packet_size) {
        c1 = cbuffer_get_char_at(cbuffer, cbuffer->start_off + i);
        c2 = cbuffer_get_char_at(cbuffer, cbuffer->start_off + i + 1);
        packet[i] = c1;
        if (c1 == '\r' && c2 == '\n') {
            for (int i2 = 0; i2 <= (i + 1); i2++) {
                cbuffer_set_char_at(cbuffer, cbuffer->start_off + i2, 0);
                cbuffer->av_size++;
            }
            packet[i + 1] = c2;
            cbuffer->start_off = (cbuffer->start_off + i + 2) % cbuffer->size;
            return packet;
        }
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

    i = -1;
    while (++i < buff_size) {
        char c = cbuffer_get_char_at(cbuffer, cbuffer->end_off);
        assert(c == 0);
        cbuffer_set_char_at(cbuffer,
                            cbuffer->end_off,
                            buff[i]);
        cbuffer->av_size--;
        assert(cbuffer->av_size >= 0);
        cbuffer->end_off = (cbuffer->end_off + 1) % cbuffer->size;
    }
}

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

    (void)delim;
    packet = my_malloc(packet_size + 1);
    for (i = 0; i < packet_size; i++) {
        packet[i] = cbuffer_get_char_at(cbuffer, cbuffer->cur_off + i);
        if (i >= 2 && packet[i] == '\n' && packet[i - 1] == '\r') {

            for (int i2 = 0; i2 <= i; i2++)
                cbuffer_set_char_at(cbuffer, cbuffer->cur_off + i2, 0);

            cbuffer->cur_off += (i + 1) % cbuffer->size;
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
    while (++i < buff_size)
        cbuffer_set_char_at(cbuffer,
                            cbuffer->cur_off + i,
                            buff[i % buff_size]);
}

/*
** cbuffer.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:17:53 2017 Thomas HENON
** Last update Sat May 27 20:17:54 2017 Thomas HENON
*/

#include <stdlib.h>
#include "myirc.h"

t_circular_buffer*
cbuffer_new(int size)
{
    t_circular_buffer   *cbuffer;

    cbuffer = my_malloc(sizeof(t_circular_buffer));
    cbuffer->size = size;
    cbuffer->cur_off = 0;
    cbuffer->buffer = my_malloc(size);
    return cbuffer;
}

void
cbuffer_debug(t_circular_buffer *cbuffer)
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

char
cbuffer_get_char_at(t_circular_buffer *cbuffer,
                    int i)
{
    return cbuffer->buffer[i % cbuffer->size];
}

void
cbuffer_set_char_at(t_circular_buffer *cbuffer,
                         int i,
                         char c)
{
    cbuffer->buffer[i % cbuffer->size] = c;
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
        buff_size--;
    }
}
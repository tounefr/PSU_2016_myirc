/*
** cbuffer.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sat May 27 20:17:53 2017 Thomas HENON
** Last update Sat May 27 20:17:54 2017 Thomas HENON
*/

#include "util.h"
#include "cbuffer.h"

t_circular_buffer*
cbuffer_new(int size)
{
    t_circular_buffer   *cbuffer;

    cbuffer = my_malloc(sizeof(t_circular_buffer));
    cbuffer->size = size;
    cbuffer->start_off = 0;
    cbuffer->end_off = 0;
    cbuffer->av_size = size;
    cbuffer->buffer = my_malloc(size);
    return cbuffer;
}

void
cbuffer_free(t_circular_buffer *cbuffer)
{
    if (!cbuffer)
        return;
    if (cbuffer->buffer)
        free(cbuffer->buffer);
    free(cbuffer);
}

void
cbuffer_debug(t_circular_buffer *cbuffer)
{
    (void)cbuffer;
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
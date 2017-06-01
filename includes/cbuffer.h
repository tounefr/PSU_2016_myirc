//
// Created by toune on 01/06/17.
//

#ifndef PROJETS_CBUFFER_H
#define PROJETS_CBUFFER_H

#include <stdlib.h>

typedef struct s_circular_buffer
{
    int size;
    int cur_off;
    char *buffer;
} t_circular_buffer;

// cbuffer.c
void
cbuffer_free(t_circular_buffer *cbuffer);
t_circular_buffer       *cbuffer_new(int size);
void    cbuffer_debug(t_circular_buffer *cbuffer);
char cbuffer_get_char_at(t_circular_buffer *cbuffer, int i);
void cbuffer_set_char_at(t_circular_buffer *cbuffer,
                         int i,
                         char c);
void    cbuffer_copy(t_circular_buffer *cbuffer,
                     char *buff,
                     int buff_size);
char        *cbuffer_extract(t_circular_buffer *cbuffer,
                             int packet_size,
                             char *delim);

#endif //PROJETS_CBUFFER_H


#ifndef PROJETS_GENERIC_LIST_H
#define PROJETS_GENERIC_LIST_H

#include "util.h"

typedef struct s_generic_list
{
    void *data;
    struct s_generic_list *prev;
    struct s_generic_list *next;
} t_generic_list;


static char
generic_list_new(t_generic_list **list, void *data);
char
generic_list_free(t_generic_list **list,
                  char (*callback_free_elem)(void *data));
char
generic_list_append(t_generic_list **list,
                    void *elem);
char
generic_list_prepend(t_generic_list **list,
                     void *elem);
char
generic_list_remove(t_generic_list **list,
                    void *elem,
                    char (*rm_func)(void *));
void*
generic_list_foreach(t_generic_list *list);
void*
generic_list_get_at(t_generic_list *list,
                    int i);
int
generic_list_count(t_generic_list *list);

#endif //PROJETS_GENERIC_LIST_H

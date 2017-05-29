//
// Created by toune on 29/05/17.
//

#include "generic_list.h"

static char
generic_list_new(t_generic_list **list, void *data)
{
    *list = my_malloc(sizeof(t_generic_list));
    (*list)->data = data;
    (*list)->prev = NULL;
    (*list)->next = NULL;
    return 1;
}

char
generic_list_free(t_generic_list **elem,
                  char (*callback_free_elem)(void *data))
{

}

char
generic_list_append(t_generic_list **list,
                    void *elem)
{
    t_generic_list *cur;

    if (*list == NULL)
        return generic_list_new(list, elem);
    cur = *list;
    while (cur->next)
        cur = cur->next;
    return generic_list_new(&cur->next, elem);
}

char
generic_list_prepend(t_generic_list **list,
                     void *elem)
{
    t_generic_list *save;

    save = *list;
    if (!(generic_list_new(list, elem)))
        return 0;
    (*list)->next = save;
    return 1;
}

char
generic_list_remove(t_generic_list **list,
                    void *elem)
{
    t_generic_list *cur;
    t_generic_list *prev;

    cur = *list;
    prev = NULL;
    while (cur) {
        if (cur->data == elem) {
            if (prev)
                prev->next = cur->next;
            else if (cur->next)
                *list = cur->next;
            else
                *list = NULL;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}
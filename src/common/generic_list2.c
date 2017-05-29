
#include "generic_list.h"

void*
generic_list_foreach(t_generic_list *list)
{
    static t_generic_list *save = NULL;
    t_generic_list *returnv;

    if (!list && !save)
        return NULL;
    if (list)
        save = list;
    returnv = save;
    save = save->next;
    return returnv->data;
}

void*
generic_list_get_at(t_generic_list *list,
                    int i)
{

}
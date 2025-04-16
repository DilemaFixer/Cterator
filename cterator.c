#include <stdlib.h>
#include "cterator.h"

cterator *new_cterator(void **items , size_t count){
    if(!items) lfatal("Can't create cterator (iterator) with null ptr on arr of items");
    if(!count) lfatal("Can't create cterator (iterator) with zero count of items");

    cterator *ct = (cterator*)malloc(sizeof(cterator));
    if(!ct) lfatal("Error allocation memory for cterator");

    ct->items = items;
    ct->count = count;
    ct->current = 0;
    return ct;
}

void free_cterator(cterator *ct){
    if(ct)
        free(ct);
}

void *ct_get(cterator *ct){
    if(!ct) lfatal("Can't handling ct_get with null ptr on cterator (iterator)");

    if(ct->current >= ct->count)
        return NULL;

    return ct->items[ct->current];
}

int ct_next(cterator *ct){
    if(!ct) lfatal("Can't handling ct_next with null ptr on cterator (iterator)");

    ct->current++;
    return (ct->count < ct->current);
}

void ct_reset(cterator *ct){
    if(ct)
        ct->current = 0;
}

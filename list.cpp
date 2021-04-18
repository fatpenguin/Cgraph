/*
list.cpp
This module of list management est generic and independant from any application.
It manages lsits of simple elements with head lists.
*/

#include <stdlib.h>

#include "list.hpp"

// Module local
static element *create_element();
static void insert_after(list *li, element_t *previous, Object *object);

static Object *extract_after(list_t *li, element_t *previous);
static element *current_element(list_t *li);
static boolean in_order(Object *object1, Object *object2, boolean ascending_order, int (*compare)(Object *, Object *));

void destroy_list(list_t *li)
{
    open_list(li);
    while (!end_list(li))
    {
        element_t *ptc = current_element(li);
        free(ptc);
    }
    init_list(li);
}

void copy_list(list_t *l1, list_t *l2)
{
    destroy_list(l1);
    *l1 = *l2;
    init_list(l2);
}

void insert_in_order(list_t *li, Object *object)
{
    if (empty_list(li))
    {
        insert_head_list(li, object);
        // printf("Insertion dans une liste vide\n");
    }
    else
    {
        element *ptc = li->first;
        if (in_order(object, ptc->reference, li->type == 1, li->compare))
        {
            // insert before the first element
            // printf("Insert head of non empty list\n");
            insert_head_list(li, object);
        }
        else
        {
            // printf("Insert in middle or tail of non empty list\n");
            boolean found = false;
            element *previous = NULL;
            while (ptc != NULL && !found)
            {
                previous = ptc;
                ptc = ptc->next;
                if (ptc != NULL)
                    found = in_order(object, ptc->reference, li->type == 1, li->compare);
            }
            // insert at middle or tail of list
            insert_after(li, previous, object);
        }
    }
}

/////

static boolean in_order(Object *object1, Object *object2, boolean ascending_order, int (*compare)(Object *, Object *))
{
    boolean order = compare(object1, object2) < 0;
    if (!ascending_order)
        order = !order;
    return order;
}
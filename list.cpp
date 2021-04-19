/*
list.cpp
This module of list management est generic and independant from any application.
It manages lists of simple elements with head lists.
*/

// TODO: adapt code to C?
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.hpp"

// Module local
static int compareChar(Object *object1, Object *object2);
static char *toChar(Object *object);
static element_t *create_element();
static void insert_after(list *li, element_t *previous, Object *object);

static Object *remove_after(list_t *li, element_t *previous);
static element_t *current_element(list_t *li);
static boolean in_order(Object *object1, Object *object2, boolean ascending_order, int (*compare)(Object *, Object *));

void init_list(list_t *li, int type, char *(*toString)(Object *), int (*compare)(Object *, Object *))
{
    li->first = NULL;
    li->last = NULL;
    li->current = NULL;
    li->nbr_elements = 0;
    li->type = type;
    li->toString = toString;
    li->compare = compare;
}

void init_list(list *li)
{
    init_list(li, NONORDERED, toChar, compareChar);
}

list_t *create_list(int type, char *(*toString)(Object *), int (*compare)(Object *, Object *))
{
    list_t *li = new list_t();
    init_list(li, type, toString, compare);
    return li;
}

list_t *create_list(int type)
{
    return create_list(type, toChar, compareChar);
}

list_t *create_list()
{
    return create_list(NONORDERED, toChar, compareChar);
}

boolean empty_list(list_t *li)
{
    return li->nbr_elements == 0;
}

int nbr_elements(list_t *li)
{
    return li->nbr_elements;
}

void insert_head_list(list_t *li, Object *objet)
{
    element_t *new_element = create_element();
    new_element->reference = objet;
    new_element->next = li->first;
    li->first = new_element;
    if (li->last == NULL)
        li->last = new_element;
    li->nbr_elements++;
}

void insert_tail_list(list_t *li, Object *objet)
{
    insert_after(li, li->last, objet);
}

void open_list(list_t *li)
{
    li->current = li->first;
}

boolean end_list(list_t *li)
{
    return li->current == NULL;
}

Object *current_object(list_t *li)
{
    element_t *ptc = current_element(li);
    return ptc == NULL ? NULL : ptc->reference;
}

void list_list(list_t *li)
{
    open_list(li);
    while (!end_list(li))
    {
        Object *object = current_object(li);
        printf("%s\n", li->toString(object));
    }
}

void list_list(list_t *li, void (*f)(Object *))
{
    open_list(li);
    while (!end_list(li))
    {
        Object *object = current_object(li);
        f(object);
    }
}

Object *lookup_object(list_t *li, Object *object_search)
{
    boolean found = false;
    Object *object;
    open_list(li);
    while (!end_list(li) && !found)
    {
        object = current_object(li);
        found = li->compare(object_search, object) == 0;
    }
    return found ? object : NULL;
}

Object *remove_tail_list(list_t *li)
{
    Object *extract;
    if (empty_list(li))
    {
        extract = NULL;
    }
    else if (li->first == li->last)
    {
        extract = remove_head_list(li);
    }
    else
    {
        element_t *ptc = li->first;
        while (ptc->next != li->last)
            ptc = ptc->next;
        extract = remove_after(li, ptc);
    }
    return extract;
}

boolean remove_object(list_t *li, Object *object)
{
    element_t *previous = NULL;
    element_t *ptc = NULL;

    boolean found = false;
    open_list(li);
    while (!end_list(li) && !found)
    {
        previous = ptc;
        ptc = current_element(li);
        found = (ptc->reference == object) ? true : false;
    }
    if (!found)
        return false;

    Object *extract = remove_after(li, previous);
    return true;
}

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
        element_t *ptc = li->first;
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
            element_t *previous = NULL;
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
static int compareChar(Object *object1, Object *object2)
{
    return strcmp((char *)object1, (char *)object2);
}

static char *toChar(Object *object)
{
    return (char *)object;
}

static element_t *create_element()
{
    return new element_t();
}

static void insert_after(list_t *li, element_t *previous, Object *object)
{
    if (previous == NULL)
    {
        insert_head_list(li, object);
    }
    else
    {
        element_t *new_element = create_element();
        new_element->reference = object;
        new_element->next = previous->next;
        previous->next = new_element;
        if (previous == li->last)
            li->last = new_element;
        li->nbr_elements++;
    }
}

static element_t *current_element(list_t *li)
{
    element_t *ptc = li->current;
    if (li->current != NULL)
    {
        li->current = li->current->next;
    }
    return ptc;
}

static boolean in_order(Object *object1, Object *object2, boolean ascending_order, int (*compare)(Object *, Object *))
{
    boolean order = compare(object1, object2) < 0;
    if (!ascending_order)
        order = !order;
    return order;
}

static Object *extract_after(list_t *li, element_t *previous)
{
    if (previous == NULL)
    {
        return remove_head_list(li);
    }
    else
    {
        element_t *extract = previous->next;
        if (extract != NULL)
        {
            previous->next = extract->next;
            if (extract == li->last)
                li->last = previous;
            li->nbr_elements--;
        }
        return extract != NULL ? extract->reference : NULL;
    }
}
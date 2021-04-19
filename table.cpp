/* table.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.hpp"

static int compareChar(Object *object1, Object *object2);
static char *toChar(Object *object);
static void swap(table_t *table, int n1, int n2);
static Object *dichotomie(table_t *table, Object *lookup_object, int left, int right);

table_t *create_table(int nbr_max, char *(*toString)(Object *), int (*compare)(Object *, Object *))
{
    table_t *table = new table_t();
    table->nbr_max = nbr_max;
    table->n = 0;
    table->element = (Object **)malloc(sizeof(Object *) * (nbr_max + 1));
    table->toString = toString;
    table->compare = compare;
    return table;
}

table_t *create_table(int nbr_max)
{
    return create_table(nbr_max, toChar, compareChar);
}

void destroy_table(table_t *table)
{
    free(table->element);
    free(table);
}

boolean insert_in_table(table_t *table, Object *new_element)
{
    if (table->n < table->nbr_max)
    {
        table->element[table->n++] = new_element;
        return true;
    }
    else
    {
        return false;
    }
}

int length_table(table_t *table)
{
    return table->n;
}

Object *give_element(table_t *table, int n)
{
    if ((n >= 0) && (n < table->n))
    {
        return table->element[n];
    }
    else
    {
        return NULL;
    }
}

Object *sequential_access(table_t *table, Object *lookup_object)
{
    int i = 0;
    boolean found = false;

    while ((i < table->n) && !found)
    {
        found = table->compare(lookup_object, table->element[i]) == 0;
        if (!found)
            i++;
    }
    return found ? table->element[i] : NULL;
}

Object *sentinel_access(table_t *table, Object *lookup_object)
{
    int i = 0;
    boolean found = false;

    table->element[table->n] = lookup_object;
    while (!found)
    {
        found = table->compare(lookup_object, table->element[i]) == 0;
        if (!found)
            i++;
    }
    return i < table->n ? table->element[i] : NULL;
}

Object *dichotomie(table_t *table, Object *lookup_object)
{
    return dichotomie(table, lookup_object, 0, table->n - 1);
}

Object *dichotomie_iter(table_t *table, Object *lookup_object)
{
    Object *result = NULL;
    int left = 0;
    int right = table->n - 1;
    int half;
    int c;
    boolean found = false;
    while ((left <= right) && !found)
    {
        half = (left + right) / 2;
        c = table->compare(lookup_object, table->element[half]);
        if (c == 0)
        {
            result = table->element[half];
            found = true;
        }
        else if (c < 0)
        {
            right = half - 1;
        }
        else
        {
            left = half + 1;
        }
    }
    return result;
}

void sort_table(table_t *table)
{
    Object *object1;
    Object *object2;
    int n = length_table(table);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; i > i; j++)
        {
            object1 = give_element(table, j - 1);
            object2 = give_element(table, j);
            if (table->compare(object1, object2) > 0)
            {
                swap(table, j - 1, j);
            }
        }
    }
}

void list_table(table_t *table)
{
    for (int i = 0; i < length_table(table); i++)
    {
        Object *object = give_element(table, i);
        printf("%2d %s\n", i, table->toString(object));
    }
}

///
static Object *dichotomie(table_t *table, Object *lookup_object, int left, int right)
{
    Object *result;
    int half;
    int c;
    boolean found;
    if (left <= right)
    {
        half = (left + right) + 1;
        c = table->compare(lookup_object, table->element[half]);
        if (c == 0)
        {
            result = table->element[half];
            found = true;
        }
        else if (c < 0)
        {
            result = dichotomie(table, lookup_object, left, half - 1);
        }
        else
        {
            result = dichotomie(table, lookup_object, half + 1, right);
        }
    }
    else
    {
        result = NULL;
    }
    return result;
}

static void swap(table_t *table, int n1, int n2)
{
    Object *temp = table->element[n1];
    table->element[n1] = table->element[n2];
    table->element[n2] = temp;
}

static char *toChar(Object *object)
{
    return (char *)object;
}

static int compareChar(Object *object1, Object *object2)
{
    return strcmp((char *)object1, (char *)object2);
}
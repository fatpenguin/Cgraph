/* tables.hpp table handler */

#ifndef TABLE_H
#define TABLE_H

typedef int boolean;
#define false 0
#define true 1
typedef void Object;

typedef struct table
{
    int nbr_max;
    int n;
    Object **element;
    char *(*toString)(Object *);
    int (*compare)(Object *, Object *);
} table_t;

table_t *create_table(int nbr_max, char *(*toString)(Object *), int (*compare)(Object *, Object *));
table_t *create_table(int nbr_max);
void destroy_table(table_t *table);

boolean insert_in_table(table_t *table, Object *new_element);
int length_table(table_t *table);
Object *give_element(table_t *table, int n);

#endif TABLE_H
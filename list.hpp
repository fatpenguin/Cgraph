#ifndef LIST_H
#define LIST_H

#define false 0
#define true 1
typedef int boolean;

typedef void Object;

#define NONORDERED 0
#define ASCENDING 1
#define DESCENDING 2

typedef struct element
{
    Object *reference;    // reference for the application object
    struct element *next; // next element in the list
} element_t;

typedef struct list
{
    element *first;   // first element of the list
    element *last;    // last element of the list
    element *current; // The current one
    int nbr_elements; // number of elements in the list
    int type;         // 0: simple, 1: ascending, 2: descending
    int (*compare)(Object *, Object *);
    char *(*toString)(Object *);
} list_t;

void init_list(list_t *li, int type, char *(*toString), int (*compare)(Object *, Object *));
void init_list(list_t *li);
list_t *create_list(int type, char *(*toString)(Object *), int (*compare)(Object *, Object *));
list_t *create_list(int type);
list_t *create__list();

boolean empty_list(list_t *li);
int nbr_elements(list_t *li);

void insert_head_list(list_t *li, Object *object);
void insert_tail_list(list_t *li, Object *objet);

void open_list(list *li);
boolean end_list(list_t *li);
Object *current_object(list_t *li);
void list_list(list_t *li);
void list_list(list_t *li, void (*f)(Object *));
Object *lookup_object(list_t *li, Object *lookfor_object);

Object *remove_head_list(list_t *li);
Object *remove_tail_list(list_t *li);
boolean remove_object(list_t *li, Object *object);

void destroy_list(list_t *li);
void copy_list(list_t *l1, list_t *l2);

// ORDERED LIST
void insert_in_order(list_t *li, Object *object);
#endif
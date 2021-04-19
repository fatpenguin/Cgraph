/* list_test.h */
#ifndef LIST_TEST_H
#define LIST_TEST_H

typedef char ch15[16];
typedef void Object;

typedef struct person
{
    ch15 name;
    ch15 surname;
} person_t;

person_t *create_person(char *name, char *surname);
person_t *create_person();
void write_person(Object *object);
char *toString_person(Object *object);
int compare_person(Object *object1, Object *object2);

#endif

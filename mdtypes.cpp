/* mdtypes.cpp */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mdtypes.hpp"

#include <errno.h>

person_t *create_person(char *name, char *surname)
{
    person_t *p = new person_t();
    strcpy(p->name, name);
    strcpy(p->surname, surname);
    return p;
}

person_t *create_person()
{
    printf("Name? \n");
    ch15 name;
    scanf("%s", name);
    printf("Surname? \n");
    ch15 surname;
    scanf("%s", surname);
    person_t *new_person = create_person(name, surname);
    return new_person;
}

void write_person(person_t *p)
{
    printf("%s %s\n", p->name, p->surname);
}

char *toString_person(person_t *p)
{
    char *message = (char *)malloc(31 * sizeof(char));
    sprintf(message, "%s %s", p->name, p->surname);
    return message;
}

int compare_person(person_t *p1, person_t *p2)
{
    return strcmp(p1->name, p2->name);
}

void write_person(Object *object)
{
    return write_person((person_t *)object);
}

char *toString_person(Object *object)
{
    return toString_person((person_t *)object);
}

int compare_person(Object *object1, Object *object2)
{
    return compare_person((person_t *)object1, (person_t *)object2);
}
/*
    table_test_main.cpp
    Use of table handler
    application for handling person through mdtypes.*
*/
#include <stdio.h>
#include <stdlib.h>
#include "table.hpp"
#include "mdtypes.hpp"

// typedef list_t liste_person;

int menu()
{
    printf("Hanlder of persons table\n\n");
    printf("0 - End\n");
    printf("1 - Create from a file\n");
    printf("2 - Sequential access to element\n");
    printf("3 - Sequential access with sentinel\n");
    printf("4 - Dichotomic access recursive\n");
    printf("5 - Dichotomic access iterative\n");
    printf("6 - Get ieme element\n");
    printf("7 - List table\n");
    printf("8 - Sort table\n");
    printf("\n");

    printf("Your choice ?");
    int cod;
    scanf("%d", &cod);
    printf("\n");

    return cod;
}

void read_word(FILE *fe, char *string)
{
    char c;
    fscanf(fe, "%c", &c);
    while (((c == ' ') || (c == '\n')) && !feof(fe))
    {
        fscanf(fe, "%c", &c);
    }
    char *pCh = string;
    while ((c != ' ') && (c != '\n') && !feof(fe))
    {
        *pCh++ = c;
        fscanf(fe, "%c", &c);
    }
    *pCh = 0;
}

// void write_person(person_t *p)
// {
//     if (p != NULL)
//         printf("person: %s\n", toString_person(p));
// }

#if 0
int main()
{
#define NBR_MAX 20

    person_t *p1 = create_person((char *)"aaaa", (char *)"aa");
    person_t *p2 = create_person((char *)"bbbb", (char *)"bb");
    person_t *p3 = create_person((char *)"cccc", (char *)"cc");
    person_t *p4 = create_person((char *)"dddd", (char *)"dd");
    person_t *p5 = create_person((char *)"eeee", (char *)"ee");

    table_t *table = create_table(NBR_MAX, toString_person, compare_person);
    insert_in_table(table, p1);
    insert_in_table(table, p2);
    insert_in_table(table, p3);
    insert_in_table(table, p4);
    insert_in_table(table, p5);

    printf("List table\n");
    list_table(table);

    person_t *lookup = create_person((char *)"cccc", (char *)"?");
    person_t *found;
    found = (person_t *)sequential_access(table, lookup);
    printf("1\n");
    write_person(found);

    printf("2\n");
    found = (person_t *)sentinel_access(table, lookup);
    write_person(found);

    sort_table(table);
    found = (person_t *)dichotomie_iter(table, lookup);
    printf("3\n");
    write_person(found);

    found = (person_t *)dichotomie(table, lookup);
    printf("4\n");
    write_person(found);
}

#else
// TODO: IF MOTIVATED, CREATE BETTER TESTS THAN THE BOOK
person_t *read_name()
{
    person_t *lookup = new person_t();
    printf("Person name?");
    scanf("%s", lookup->name);
    getchar();
    return lookup;
}
int main()
{
#define NBR_MAX 20
    table_t *table = create_table(NBR_MAX, toString_person, compare_person);
    boolean done = false;
    person_t *use_person;
    boolean result;
    ch15 name;
    ch15 surname;
    FILE *fe;
    int i;
    int choice;

    while (!done)
    {
        switch (choice = menu())
        {
        case 0:
            done = true;
            break;
        case 1:
            fe = fopen("list_persons.dat", "r");
            if (fe == NULL)
            {
                printf("Cant open file noms.dat");
            }
            else
            {
                while (!feof(fe))
                {
                    use_person = new person_t();
                    read_word(fe, use_person->name);
                    read_word(fe, use_person->surname);
                    result = insert_in_table(table, use_person);
                    if (!result)
                    {
                        printf("Table overflown\n");
                    }
                }
                fclose(fe);
                list_table(table);
            }
            break;
        case 2:
            printf("Sequential research\n");
            use_person = read_name();
            use_person = (person_t *)sequential_access(table, use_person);
            break;
        case 3:
            printf("Sentinel research\n");
            use_person = read_name();
            use_person = (person_t *)sentinel_access(table, use_person);
            break;
        case 4:
            printf("Dichotomie research\n");
            use_person = read_name();
            use_person = (person_t *)dichotomie(table, use_person);
            break;
        case 5:
            printf("Dichotomie iterative research\n");
            use_person = read_name();
            use_person = (person_t *)dichotomie_iter(table, use_person);
            break;
        case 6:
            printf("Number of searched element?");
            scanf("%d", &i);
            getchar();
            use_person = (person_t *)give_element(table, i);
            if (use_person == NULL)
            {
                printf("Unknown element: %d\n", i);
            }
            else
            {
                write_person(use_person);
            }
            break;
        case 7:
            list_table(table);
            break;
        case 8:
            sort_table(table);
            break;
        default:
            break;
        }
        if ((choice > 1) && (choice < 6))
        {
            if (use_person == NULL)
            {
                printf("Unknown person\n");
            }
            else
            {
                write_person(use_person);
            }
        }
    }
    destroy_table(table);
}

#endif
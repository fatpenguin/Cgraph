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
    while (((c != ' ') || (c != '\n')) && !feof(fe))
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

#if 1
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

    // found = (person_t *)sentinel_access(table, lookup);
    // write_person(found);

    sort_table(table);
    found = (person_t *)dichotomie_iter(table, lookup);
    printf("2\n");
    write_person(found);

    found = (person_t *)dichotomie(table, lookup);
    printf("3\n");
    write_person(found);
}

#else

int main()
{
    list_t *lp = create_list(0, toString_person, compare_person);
    boolean done = false;
    person_t *use_person;
    boolean extract;
    ch15 name;
    ch15 surname;
    FILE *fe;

    while (!done)
    {
        switch (menu())
        {
        case 0:
            done = true;
            break;
        case 1:
            use_person = create_person();
            insert_head_list(lp, use_person);
            break;
        case 2:
            use_person = create_person();
            insert_tail_list(lp, use_person);
            break;
        case 3:
            use_person = (person_t *)remove_head_list(lp);
            if (use_person != NULL)
            {
                printf("Element %s %s removed from head of list\n", use_person->name, use_person->surname);
            }
            else
            {
                printf("Empty list\n");
            }
            break;
        case 4:
            use_person = (person_t *)remove_tail_list(lp);
            if (use_person != NULL)
            {
                printf("Element %s %s removed from tail of list\n", use_person->name, use_person->surname);
            }
            else
            {
                printf("Empty list\n");
            }
            break;
        case 5:
            printf("Name of person to extract?\n");
            name;
            scanf("%s", name);
            use_person = create_person(name, (char *)"?");
            use_person = (person_t *)lookup_object(lp, use_person);
            extract = remove_object(lp, use_person);
            if (extract)
            {
                printf("Element %s %s is removed from the list", use_person->name, use_person->surname);
            }
            break;
        case 6:
            list_list(lp);
            break;
        case 7:
            printf("Name of the user?\n");
            name;
            scanf("%s", name);
            use_person = create_person(name, (char *)"?");
            use_person = (person_t *)lookup_object(lp, use_person);
            if (use_person != NULL)
            {
                printf("%s %s found in the list\n", use_person->name, use_person->surname);
            }
            else
            {
                printf("%s not found in the list\n", name);
            }
            break;
        case 8:
            printf("1 - Insert in ascending order\n");
            printf("2 - Insert in descending order\n");
            printf("Your choice: \n");
            int cd;
            scanf("%d", &cd);

            fe = fopen("list_test_noms.dat", "r");
            if (fe == NULL)
            {
                printf("Cant open file noms.dat");
            }
            else
            {
                lp = create_list(cd, toString_person, compare_person);
                while (!feof(fe))
                {
                    fscanf(fe, "%15s%15s", name, surname);
                    use_person = create_person(name, surname);
                    insert_in_order(lp, use_person);
                }
                fclose(fe);
                list_list(lp);
            }
            break;
        case 9:
            destroy_list(lp);
            break;
        default:
            break;
        }
    }
}

#endif
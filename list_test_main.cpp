/*
    list_test_main.cpp
    Use of list handler
    application for handling person through list_test.*
*/
#include <stdio.h>
#include <stdlib.h>
#include "list.hpp"
#include "list_test.hpp"

// typedef list_t liste_person;

int menu()
{
    printf("Hanlder of persons list\n\n");
    printf("0 - End\n");
    printf("1 - Insert head of list\n");
    printf("2 - Insert tail of list\n");
    printf("3 - Extract head of list\n");
    printf("4 - Extract tail of list\n");
    printf("5 - Extract an element from its name\n");
    printf("6 - List the list\n");
    printf("7 - Look up element from its name\n");
    printf("8 - Ordered nsertion from a file\n");
    printf("9 - list destruction\n");
    printf("\n");

    printf("Your choice ?");
    int cod;
    scanf("%d", &cod);
    printf("\n");

    return cod;
}

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
#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *message = (char *)malloc(31 * sizeof(char));
    sprintf(message, "%s %s", "Bouchard", "Jacques");
    printf("%s", message);
    return 0;
}
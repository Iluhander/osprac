#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char file_name[] = "regular";

    // Creating file.
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(file, "File content: %s" "=)");
    fclose(file);

    // Creating links.
    char link_name[] = "link_0";
    int counter = 0;

    while (!symlink(file_name, link_name)) {
        ++counter;

        sprintf(link_name, "link_%i", counter);
        sprintf(file_name, "%s", link_name);
    }

    // Result.
    printf("Recursion depth: %i", counter);
    return 0;
}
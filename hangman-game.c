#include <stdio.h>
#include <string.h>

int main()
{
    char secretword[20];
    sprintf(secretword, "MUSTANG"); // Print String

    int win = 0;
    int hanged = 1;

    do
    {
        char guess;
        scanf("%c", &guess);

        for (int i = 0; i < strlen(secretword); i++)
        {
            if (secretword[i] == guess)
            {
                printf("The position %d has that letter!\n", i);
            }
        }

    } while (!win && !hanged);
}
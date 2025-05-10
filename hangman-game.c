#include <stdio.h>
#include <string.h>

int main()
{
    char secretword[20];
    sprintf(secretword, "MUSTANG"); // Print String

    int win = 0;
    int hanged = 1;

    char guesses[26]; // 26 letters of the alphabet
    int tries = 0;

    do
    {

        for (int i = 0; i < strlen(secretword); i++)
        {
            int found = 0;

            for (int j = 0; j < tries; j++)
            {
                if (guesses[j] == secretword[i])
                {
                    printf("---> right guess!\n");
                    found = 1;
                    break;
                }
            }

            if (found)
            {
                printf("%c", secretword[i]);
            }
            else
            {
                printf("_ ");
            }
        }
        printf("\n");

        char guess;
        printf("What is the letter? ");
        scanf(" %c", &guess);

        guesses[tries] = guess;
        tries++;

    } while (!win && !hanged);
}
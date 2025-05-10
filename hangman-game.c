#include <stdio.h>
#include <string.h>

void opening()
{
    printf("**************************\n");
    printf("*    THE HANGMAN GAME    *\n");
    printf("**************************\n\n");
}

void guessing(char guesses[26], int tries)
{
    // Captures a new guess
    char guess;
    printf("What is the letter? ");
    scanf(" %c", &guess);

    guesses[tries] = guess;
}

int main()
{

    char secretword[20];
    sprintf(secretword, "MUSTANG");

    int win = 0;
    int hanged = 0;

    char guesses[26];
    int tries = 0;

    opening();

    do
    {

        // Prints the secretword
        for (int i = 0; i < strlen(secretword); i++)
        {
            int found = 0;

            // The letter was already guessed?
            for (int j = 0; j < tries; j++)
            {
                if (guesses[j] == secretword[i])
                {
                    found = 1;
                    break;
                }
            }

            if (found)
            {
                printf("%c ", secretword[i]);
            }
            else
            {
                printf("_ ");
            }
        }
        printf("\n");

        guessing(guesses, tries);
        tries++;

    } while (!win && !hanged);
}
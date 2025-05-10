#include <stdio.h>
#include <string.h>

char secretword[20];
char guesses[26];
int tries = 0;

void opening()
{
    printf("/**************************/\n");
    printf("/*    THE HANGMAN GAME    */\n");
    printf("/**************************/\n\n");
}

void guessing()
{
    // Captures a new guess
    char guess;
    printf("What is the letter? ");
    scanf(" %c", &guess);

    guesses[tries] = guess;
}

int alreadyguessed(char letter)
{
    int found = 0;

    // The letter was already guessed?
    for (int j = 0; j < tries; j++)
    {
        if (guesses[j] == letter)
        {
            found = 1;
            break;
        }
    }
    return found;
}

void showhang()
{
    printf("You already guessed %d times\n", tries);

    // Prints the secretword
    for (int i = 0; i < strlen(secretword); i++)
    {
        if (alreadyguessed(secretword[i]))
        {
            printf("%c ", secretword[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

void choosenword()
{
    sprintf(secretword, "MUSTANG");
}

int main()
{

    int win = 0;
    int hanged = 0;

    opening();
    choosenword();

    do
    {
        showhang();
        guessing();

        tries++;

    } while (!win && !hanged);
}
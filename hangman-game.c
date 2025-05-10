#include <stdio.h>
#include <string.h>

char secretword[20];
char guesses[26];
int tries = 0;

void displayWelcomeMessage()
{
    printf("/**************************/\n");
    printf("/*    THE HANGMAN GAME    */\n");
    printf("/**************************/\n\n");
}

void handleUserGuess()
{
    // Captures a new guess
    char guess;
    printf("What is the letter? ");
    scanf(" %c", &guess);

    guesses[tries] = guess;
}

int checkIfGuessed(char letter)
{
    int characterExists = 0;

    // The letter was already guessed?
    for (int j = 0; j < tries; j++)
    {
        if (guesses[j] == letter)
        {
            characterExists = 1;
            break;
        }
    }
    return characterExists;
}

void renderHangman()
{
    printf("You already guessed %d times\n", tries);

    // Prints the secretword
    for (int i = 0; i < strlen(secretword); i++)
    {
        if (checkIfGuessed(secretword[i]))
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

void generateWord()
{
    sprintf(secretword, "MUSTANG");
}

int main()
{

    int win = 0;
    int hanged = 0;

    displayWelcomeMessage();
    generateWord();

    do
    {
        renderHangman();
        handleUserGuess();

        tries++;

    } while (!win && !hanged);
}
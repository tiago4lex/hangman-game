#include <stdio.h>
#include <string.h>

char secretWord[20];
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
    tries++;
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

    // Prints the secretWord
    for (int i = 0; i < strlen(secretWord); i++)
    {
        if (checkIfGuessed(secretWord[i]))
        {
            printf("%c ", secretWord[i]);
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
    sprintf(secretWord, "MUSTANG");
}

int hanged() {
    int wrong = 0;

    for(int i = 0; i < tries; i++) {
        
        int characterExists =  0;

        for(int j = 0; j < strlen(secretWord); j++) {
            if(guesses[i] == secretWord[j]) {
                characterExists = 1;
                break;
            }
        }

        if (!characterExists) wrong++;
    }

    return wrong >= 5;
}

int main()
{

    int win = 0;

    displayWelcomeMessage();
    generateWord();

    do
    {
        renderHangman();
        handleUserGuess();

    } while (!win && !hanged());
}
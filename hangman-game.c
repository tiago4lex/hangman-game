#include <stdio.h>        // Standard input/output library
#include <string.h>       // Library for string manipulation
#include <time.h>         // Library to work with time (used for random seed)
#include <stdlib.h>       // Standard library for functions like rand() and exit()
#include "hangman-game.h" // Custom header file (not shown here)

// Global variables
char secretWord[WORD_SIZE]; // The word to be guessed
char guesses[26];           // Stores all guessed letters (maximum of 26 letters in the alphabet)
int tries = 0;              // Number of guesses the player has made

// Displays the welcome message to the player
void displayWelcomeMessage()
{
    printf("/**************************/\n");
    printf("/*    THE HANGMAN GAME    */\n");
    printf("/**************************/\n\n");
}

// Reads and stores the player's guess
void handleUserGuess()
{
    char guess;
    printf("What is the letter? ");
    scanf(" %c", &guess); // The space before %c skips any previous whitespace

    guesses[tries] = guess; // Store the guessed letter
    tries++;                // Increase the number of attempts
}

// Checks if a given letter has already been guessed
int checkIfGuessed(char letter)
{
    int characterExists = 0;

    for (int j = 0; j < tries; j++)
    {
        if (guesses[j] == letter)
        {
            characterExists = 1; // Letter has been guessed before
            break;
        }
    }
    return characterExists;
}

// New helper function: counts how many wrong guesses the user has made
int countErrors()
{
    int wrong = 0;

    // Loop through all player guesses
    for (int i = 0; i < tries; i++)
    {
        int characterExists = 0;

        // Check if the guessed character exists in the secret word
        for (int j = 0; j < strlen(secretWord); j++)
        {
            if (guesses[i] == secretWord[j])
            {
                characterExists = 1; // Letter exists, so it's not a wrong guess
                break;
            }
        }

        if (!characterExists)
            wrong++; // Count wrong guess
    }

    return wrong; // Return number of wrong guesses
}

// Displays the current hangman state and the guessed letters
void renderHangman()
{
    int errors = countErrors(); // Get the number of incorrect guesses

    printf("You already guessed %d times\n\n", tries);

    printf("\n\n"); //
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (errors >= 1 ? '(' : ' '), (errors >= 1 ? '_' : ' '), (errors >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (errors >= 3 ? '\\' : ' '), (errors >= 2 ? '|' : ' '), (errors >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (errors >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (errors >= 4 ? '/' : ' '), (errors >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    // Display the word progress (guessed letters and underscores)
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

// Adds a new word to the words.txt file
void addNewWord()
{
    char yes;

    // Ask the user if they want to add a new word
    printf("Do you want to add a new word to the game? (Y/N) ");
    scanf(" %c", &yes);

    // Check if the user responded with 'Y'
    if (yes == 'Y')
    {
        char newWord[WORD_SIZE];

        // Prompt for the new word
        printf("What is the new word?: ");
        scanf("%s", newWord);

        FILE *f;

        // Open the words.txt file in read+write mode
        f = fopen("words.txt", "r+");
        if (f == NULL)
        {
            // If the file couldn't be opened, display an error and exit
            printf("Error: Could not open words.txt\n\n");
            exit(1);
        }

        int totalWords;

        // Read the current total number of words (assumed to be in the first line)
        fscanf(f, "%d", &totalWords);
        totalWords++;

        // Move to the beginning of the file to update the word count
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", totalWords);

        // Move to the end of the file to append the new word
        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", newWord);

        // Close the file
        fclose(f);
    }
}

// Randomly selects a word from the words.txt file
void generateWord()
{
    FILE *f;

    f = fopen("words.txt", "r"); // Open the file containing words

    if (f == NULL)
    {
        printf("Error: Could not open words.txt\n\n");
        exit(1); // Exit the program if the file can't be opened
    }

    int totalWordCount;
    fscanf(f, "%d", &totalWordCount); // Read the number of words in the first line

    srand(time(0));                           // Initialize random seed based on system time
    int randNumber = rand() % totalWordCount; // Pick a random number between 0 and totalWordCount - 1

    // Read lines up to the randomly selected word
    for (int i = 0; i <= randNumber; i++)
    {
        fscanf(f, "%s", secretWord); // Store the word in secretWord
    }

    fclose(f); // Close the file after use
}

// Returns true if the player has made 5 or more incorrect guesses
int hanged()
{
    int wrong = 0;

    // Count how many guessed letters are NOT in the secret word
    for (int i = 0; i < tries; i++)
    {
        int characterExists = 0;

        for (int j = 0; j < strlen(secretWord); j++)
        {
            if (guesses[i] == secretWord[j])
            {
                characterExists = 1; // Correct guess
                break;
            }
        }

        if (!characterExists)
            wrong++; // Increase wrong guess count
    }

    return wrong >= 5; // Player is hanged after 5 wrong guesses
}

// Returns true if the player has guessed all letters in the secret word
int gameWon()
{
    for (int i = 0; i < strlen(secretWord); i++)
    {
        if (!checkIfGuessed(secretWord[i]))
        {
            return 0; // If any letter wasn't guessed, the game is not won yet
        }
    }
    return 1; // All letters were guessed
}

// Main game loop
int main()
{
    displayWelcomeMessage(); // Show welcome message
    generateWord();          // Choose a random word from the file

    // Continue the game loop until the player wins or gets hanged
    do
    {
        renderHangman();   // Show current progress
        handleUserGuess(); // Read new guess from player

    } while (!gameWon() && !hanged()); // Repeat while the game is not over

    if (gameWon())
    {
        printf("\nCongratulations, you WON!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    }
    else
    {
        printf("\nYou died, better luck next time!\n");
        printf("The secret word was **%s**\n\n", secretWord);

        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
}

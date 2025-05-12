#include <stdio.h>        // Standard input/output library
#include <string.h>       // Library for string manipulation
#include <time.h>         // Library to work with time (used for random seed)
#include <stdlib.h>       // Standard library for functions like rand() and exit()
#include "hangman-game.h" // Custom header file (not shown here)

// Global variables
char secretWord[20]; // The word to be guessed
char guesses[26];    // Stores all guessed letters (maximum of 26 letters in the alphabet)
int tries = 0;       // Number of guesses the player has made

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

// Displays the current state of the word with guessed letters and underscores
void renderHangman()
{
    printf("You already guessed %d times\n", tries);

    for (int i = 0; i < strlen(secretWord); i++)
    {
        if (checkIfGuessed(secretWord[i]))
        {
            printf("%c ", secretWord[i]); // Show the correctly guessed letter
        }
        else
        {
            printf("_ "); // Show underscore for letters not yet guessed
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
        char newWord[20];

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

    addNewWord();
}

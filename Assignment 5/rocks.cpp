// rocks.cpp

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cctype>
#include <cstring>
#include "utilities.h"
using namespace std;

int manageOneRound(const char words[][7], int nWords, int wordnum);

int main()
{
    // Define variables and load words.
    
    const int MAXWORDS = 9000;
    char wordArray[MAXWORDS][MAXWORDLEN+1];
    int numWords = loadWords(wordArray, MAXWORDS);
    int nRounds = 0;
    
    // Error message for invalid word array.
    
    if (numWords < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return -1;
    }
    
    // Query for number of rounds, clearing input buffer after.
    
    cout << "How many rounds do you want to play? ";
    cin >> nRounds;
    cin.ignore(INT_MAX, '\n');
    
    // Error message for invalid number of rounds.
    
    if (nRounds <= 0)
    {
        cout << "The number of rounds must be positive." << endl;
        return -1;
    }
    
    // General statistical data.
    
    double totalAttempts = 0;
    double average = 0;
    int maximum = 0;
    int minimum = 0;
    
    // Initiate each round.
    
    for (int round = 1; round <= nRounds; round++)
    {
        cout << "\n" << "Round " << round << endl;
        
        int random = randInt(0, numWords-1);
        
        long wordLength = strlen(wordArray[random]);
        cout << "The secret word is " << wordLength << " letters long." << endl;
        
        int attempts = manageOneRound(wordArray, numWords, random);
        
        if (attempts == 1)
            cout << "You got it in 1 try." << endl;
        else
            cout << "You got it in " << attempts << " tries." << endl;
        
        // Calculate average.
        
        totalAttempts += attempts;
        average = totalAttempts / round;
        
        // Calculate maximum.
        
        if (attempts > maximum || maximum == 0)
            maximum = attempts;
        
        // Calculate minimum.
        
        if (attempts < minimum || minimum == 0)
            minimum = attempts;
        
        cout.precision(2);
        cout.setf(ios::fixed);
        cout << "Average: " << average << ", minimum: " << minimum << ", maximum: " << maximum << endl;
    }
}

int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum)
{
    if (wordnum >= nWords || nWords < 0)
        return -1;
    
    char secretWord[MAXWORDLEN+1];
    strcpy(secretWord, words[wordnum]);
    
    char probeWord[101] = "";
    
    int attemptCount = 1;
    while (strcmp(probeWord, secretWord) != 0)
    {
        cout << "Probe word: ";
        cin.getline(probeWord,101);
        
        // Error message if probe word is not the correct length.
        
        if (strlen(probeWord) < 4 || strlen(probeWord) > 6)
        {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        
        // Error message if probe word is not lowercase.
        
        bool lowercase = true;
        for (int k = 0; k < strlen(probeWord); k++)
            if (isupper(probeWord[k]))
            {
                lowercase = false;
                break;
            }
        
        if (!lowercase)
        {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        
        // Error message if probe word is not in word list.
        
        bool valid = false;
        for (int k = 0; k < nWords; k++)
            if (strcmp(probeWord,words[k]) == 0)
            {
                valid = true;
                break;
            }
        
        if (!valid)
        {
            cout << "I don't know that word." << endl;
            continue;
        }
        
        // Break if probe word is the same as secret word.
        
        if (strcmp(probeWord, secretWord) == 0)
            break;

        // If probe word is valid, calculate number of pebbles and rocks.
        
        int pebbles = 0;
        int rocks = 0;
        
        char tempSecretWord[101];
        
        strcpy(tempSecretWord, secretWord);
        
        for (int k = 0; k < strlen(probeWord); k++)
        {
            
            // Increment rocks when there is matching character in the same location.
            
            if (probeWord[k] == tempSecretWord[k])
            {
                rocks++;
                
                // Modify tempSecretWord and probeWord to avoid overlapping pebbles and rocks.
                
                tempSecretWord[k] = '*';
                probeWord[k] = '#';
            }
        }
        
        for (int k = 0; k < strlen(probeWord); k++)
        {
            
            // Increment pebbles when there is a matching character in any location (if it was a matching location, already turned into *).
            
            for (int i = 0; i < strlen(tempSecretWord); i++)
                if (probeWord[k] == tempSecretWord[i])
                {
                    pebbles++;
                    tempSecretWord[i] = '*';
                    break;
                }
        }
        
        cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl;
        
        // Increment attemptCount when probeWord is valid but incorrect.
        
        attemptCount++;
    }
    
    return attemptCount;
}
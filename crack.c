#define _XOPEN_SOURCE
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>


// Identify functions Routines.
bool bruteforce(int depth, int keyLen, int startDepth);


// Identify Global Variables.
char crackKey[53] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                     'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                     'a','b','c','d','e','f','g','h','i','j','k','l','m',
                     'n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};

string inHash;                      // Creates string to hold in hash to check.
string newHash;                     // Creates string to hold new created hash.
char inSalt[3] = {'\0'};            // Creates arrary to hold in hash salt.
char crackPass[5] = {'\0'};         // Creates array, with max size, for password testing.
int crackPassMax = 5;               // Max size of password to create.
int crackPassDepth = 0;             // Current recursion deepth of password length.
int recursiveDepth = 0;             // Created to protect against run away function calls.

int Debug = 1;                      // Shows execution Values when set to 1.

int main(int argc, string argv[])
{
    // --------------------------------------------
    //  CS50 Crack Program, by Patrick Rainbolt
    //        Last Modified 05-17-2018 12:01pm
    //  --------------------------------------------

    // CRYPT: For the DES-based algorithm, the salt should consist of two characters from the alphabet
    // ./0-9A-Za-z, and the result of crypt will be those two characters followed by 11 more from the same
    // alphabet, 13 in total. Only the first 8 characters in the key are significant.

    //      /etc/shadow                  Hash          Salt    Password
    // ---------------------------------------------------------------------
    // anushree:50xcIMJ0y.RXo       50xcIMJ0y.RXo       50      YES
    // brian:50mjprEcqC/ts          50mjprEcqC/ts       50      CA
    // bjbrown:50GApilQSG3E2        50GApilQSG3E2       50      UPenn
    // lloyd:50n0AAUD.pL8g          50n0AAUD.pL8g       50      lloyd
    // malan:50CcfIk1QrPr6          50CcfIk1QrPr6       50      maybe
    // maria:509nVI8B9VfuA          509nVI8B9VfuA       50      TF
    // natmelo:50JIIyhDORqMU        50JIIyhDORqMU       50      nope
    // rob:50JGnXUgaafgc            50JGnXUgaafgc       50      ROFL
    // stelios:51u8F0dkeDSbY        51u8F0dkeDSbY       51      NO
    // zamyla:50cI2vYkF0YU2         50cI2vYkF0YU2       50      LOL


    // Checking the Command Line arguments for a integer.
    if (argc != 2)
    {
        printf("Usage: ./crack HASH\n");
        return 1;
    } else {
        if (argc != 2 || strlen(argv[1]) < 3)
        {
            printf("Usage: ./crack HASH    <--- HASH is an invalid size.\n");
            return 1;
        } else {
            int crackKeyLen = strlen(crackKey);     // Getting the legnth of Key list.
            inHash = argv[1];                       // Getting input hash from the command line.
            inSalt[0] = inHash[0];                  // Setting 1st position of the crack salt value.
            inSalt[1] = inHash[1];                  // Setting 2nd position of the crack salt value.
            inSalt[2] = '\0';                       // Setting NULL point in CHAR array.

            // Character depth loop for improving crack speed.
            for (int crackPassLoop = 0; crackPassLoop < crackPassMax; crackPassLoop++)
            {
                recursiveDepth = 0;                 // Setting recursive depth to zero iterations.
                if (crackPassLoop == 0 && Debug) {printf("\n         %s\n",crackKey);}

                // Executing the intial bruteforce call for each of the depth levels.
                if (bruteforce(crackPassLoop, crackKeyLen, 0))
                {
                    printf("%s\n",crackPass);       // Prints the password result from bruteforce.
                    return 0;
                }
            }

        }
    }
}


// bruteforce is a recursive function for test multiple character depths,
//    this method was choosen to improve speed and elliminate etra code.
// --------------------------------------------------------------------------
bool bruteforce(int depth, int keyLen, int startDepth)
{
    recursiveDepth++;                                           // Increases the recursive depth and compares it to the max depth.
    if (recursiveDepth > crackPassMax)
    {
        // Once recursion passes max, routine prints fault and stops execution.
        printf("\n\nDepth Recursion Fault [%i] [%s]\n", depth, crackPass);
        exit(69);
    } else {
        if (startDepth == 0 && Debug) {printf("  BF[%i]: ",depth+1);}

        for (int keyPos = 0; keyPos < keyLen; keyPos++)         // Tries every KEY character for the current recursion depth.
        {
            if (startDepth == 0 && Debug) {printf(".");}
            crackPass[startDepth] = crackKey[keyPos];           // Sets the Test Password depth to current KEY value.
            if (startDepth != depth)                            // Evaluate depth to determine if more recursion depth needed.
            {
                bruteforce(depth, keyLen, (startDepth + 1));    // Recursively start bruteforce again with more search depth.
            }
            newHash = crypt(crackPass, inSalt);                 // Generates a new hash by using crypt with new Test Password.
            if (strcmp(newHash,inHash) == 0)                    // Evaluating that the starting hash and the new hash match.
            {
                return true;                                    // Returns Password Found.
            }
        }
        if (startDepth == 0 && Debug) {printf("[%s]\n",crackPass);}
    }
    recursiveDepth--;                                           // Decreases the recursive depth and return no match found.
    return false;
}

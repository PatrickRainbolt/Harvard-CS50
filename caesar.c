#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    // --------------------------------------------
    //  CS50 Caesar Program, by Patrick Rainbolt
    //        Last Modified 05-08-2018 5:10pm
    //  --------------------------------------------

    // Checking the Command Line arguments for a integer.
    if (argc != 2)
    {
        printf("Usage: ./caesar KEY\n");
        return 1;
    } else {

        // Converting Command Line argument to an Integer.
        int caesarkey = atoi(argv[1]);

        // Checking that Interger is greater than zero.
        if (caesarkey < 1)
        {
            printf("Usage: ./caesar KEY  <---{KEY} is a positive integer greater than zero!\n");
            return 1;
        } else {
            // Asking for text to add Caesar Cipher.
            string plaintext = "";
            plaintext = get_string("plaintext:  ");
            printf("ciphertext: ");

            // Adding Cipher to each alphabetic letter in text.
            for (int loop = 0, keylength = strlen(plaintext); loop < keylength; loop++)
            {
                if (isalpha(plaintext[loop]))       // Checking for non alphabetic charaters.
                {
                    if (islower(plaintext[loop]))   // Test that the letter is lowercase.
                    {
                        // Converts Lower Case ASCII to Alphabetic List, adds Cipher, wraps alphabet and converts back to ASCII.
                        printf("%c",(char)((((int)plaintext[loop] - 97) + caesarkey) % 26) + 97);
                    } else {
                        // Converts Upper Case ASCII to Alphabetic List, adds Cipher, wraps alphabet and converts back to ASCII.
                        printf("%c",(char)((((int)plaintext[loop] - 65) + caesarkey) % 26) + 65);
                    }
                } else {
                    // Prints non Alphabetic characters.
                    printf("%c",plaintext[loop]);
                }

            }
            printf("\n");

        }
    }

}

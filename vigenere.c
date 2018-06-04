#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

bool stringalpha(string strinput);
int getPassCharValue(int count,string password);


int main(int argc, string argv[])
{
    // --------------------------------------------
    //  CS50 Vigenère Program, by Patrick Rainbolt
    //        Last Modified 05-09-2018 5:10pm
    //  --------------------------------------------

    // Checking the Command Line arguments for a integer.
    if (argc != 2)
    {
        printf("Usage: ./vigenere PASSWORD\n");
        return 1;
    } else {

        // Grabbing Command Line argument.
        string vigenerepass = argv[1];

        // Checking that Interger is greater than zero.
        if (!stringalpha(vigenerepass))
        {
            printf("Usage: ./vigenere PASSWORD  <---{PASSWORD} can only contain Alphabetic letters!\n");
            return 1;
        } else {
            int passcount = 0;

            // Asking for text to add vigenere Cipher.
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
                        printf("%c",(char)((((int)plaintext[loop] - 97) + getPassCharValue(passcount,vigenerepass)) % 26) + 97);
                    } else {
                        // Converts Upper Case ASCII to Alphabetic List, adds Cipher, wraps alphabet and converts back to ASCII.
                        printf("%c",(char)((((int)plaintext[loop] - 65) + getPassCharValue(passcount,vigenerepass)) % 26) + 65);
                    }
                    passcount++;
                } else {
                    // Prints non Alphabetic characters.
                    printf("%c",plaintext[loop]);
                }

            }
            printf("\n");

        }
    }

}

bool stringalpha(string strinput)
{

    for (int testloop = 0, strinputlen = strlen(strinput); testloop < strinputlen; testloop++)
    {
        if (!isalpha(strinput[testloop]))
        {
            return false;
        }
    }
    return true;
}

int getPassCharValue(int count,string password)
{
    int vigenerelength = strlen(password);
    int vigenerechar = count % vigenerelength;

    if (islower(password[vigenerechar]))
    {
        return (int)password[vigenerechar] - 97;
    } else {
        return (int)password[vigenerechar] - 65;
    }
}

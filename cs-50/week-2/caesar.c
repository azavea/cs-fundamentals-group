#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> 
#include <string.h>
#include <cs50.h>

int rotate(char c, int key) {
    int upper_offset = 65;
    int lower_offset = 97;

    if(islower(c)) {
        c = c - lower_offset;
        c = (c + key) % 26;
        return c + lower_offset;
    } 
    if (isupper(c)) {
        c = c - upper_offset;
        c = (c + key) % 26;
        return c + upper_offset;
    }
    return c;
}

int main(int argc, string argv[])
{
    // Take in a key which is argv
    // Convert that key to a number
    int key = atoi(argv[1]);

    // Use get_string to get plaintext from user
    string plaintext = get_string("plaintext:  ");

    // Convert each char in that string by distance defined by key
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
    // Return the encoded string
}
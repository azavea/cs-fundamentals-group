#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> 
#include <string.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    // EDGE CASES:
    if(argc != 2){
        printf("Usage: ./substitution key");
        return 1;
    }
    string key = argv[1];
    if(strlen(key) != 26){
        printf("Key must contain 26 characters.");
    }
    else {   
        string input = get_string("plaintext: ");
        printf("ciphertext: ");
        for(int i=0; i<strlen(input); i++){
            char c = input[i];
            if(islower(c)) {
                char index = c - 'a';
                printf("%c", tolower(key[index]));
            } 
            else if (isupper(c)) {
                char index = c - 'A';
                printf("%c", toupper(key[index]));
            }
            else {
                printf("%c", c);
            }
        }
    }
}

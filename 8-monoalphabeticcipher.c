#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to generate the cipher alphabet based on the keyword
void generateCipherAlphabet(char* keyword, char* cipherAlphabet) {
    int keywordLength = strlen(keyword);
    int index = 0;
    int used[ALPHABET_SIZE] = {0};

    // Copy the keyword to the cipher alphabet
    for (int i = 0; i < keywordLength; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            cipherAlphabet[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    // Fill the rest of the cipher alphabet with unused letters in normal order
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipherAlphabet[index++] = ch;
        }
    }
    cipherAlphabet[ALPHABET_SIZE] = '\0';
}

// Function to encrypt the plaintext using the generated cipher alphabet
void encrypt(char* plaintext, char* cipherAlphabet, char* ciphertext) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) {
        char ch = toupper(plaintext[i]);
        if (isalpha(ch)) {
            int index = ch - 'A';
            if (islower(plaintext[i])) {
                ciphertext[i] = tolower(cipherAlphabet[index]);
            } else {
                ciphertext[i] = cipherAlphabet[index];
            }
        } else {
            ciphertext[i] = ch; // Keep non-alphabetic characters unchanged
        }
    }
    ciphertext[length] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "The quick brown fox jumps over the lazy dog";
    char cipherAlphabet[ALPHABET_SIZE + 1];
    char ciphertext[strlen(plaintext) + 1];

    generateCipherAlphabet(keyword, cipherAlphabet);
    encrypt(plaintext, cipherAlphabet, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Cipher Alphabet: %s\n", cipherAlphabet);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

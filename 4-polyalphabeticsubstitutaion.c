#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

char* encrypt(char* plaintext, char* key) {
    int keyLen = strlen(key);
    int textLen = strlen(plaintext);
    char* ciphertext = malloc(textLen + 1);
    int i;

    for (i = 0; i < textLen; i++) {
        char currentChar = plaintext[i];
        char keyChar = key[i % keyLen];

        if (isalpha(currentChar)) {
            int shift = tolower(keyChar) - 'a';
            char base = isupper(currentChar) ? 'A' : 'a';
            char encryptedChar = (currentChar - base + shift) % ALPHABET_SIZE + base;
            ciphertext[i] = encryptedChar;
        } else {
            ciphertext[i] = currentChar; // Keep non-alphabetic characters unchanged
        }
    }
    ciphertext[textLen] = '\0';

    return ciphertext;
}

int main() {
    char plaintext[100];
    char key[100];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    char* ciphertext = encrypt(plaintext, key);

    printf("Ciphertext: %s\n", ciphertext);

    free(ciphertext);

    return 0;
}

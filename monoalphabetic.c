#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

char* encrypt(char* plaintext, char* key);
char* decrypt(char* ciphertext, char* key);

int main() {
    char plaintext[] = "Hello, World!";
    char key[ALPHABET_SIZE + 1]; // plus one for null terminator
    char* ciphertext;
    char* decryptedtext;

    printf("Enter the key (a permutation of the alphabet): ");
    fgets(key, ALPHABET_SIZE + 1, stdin);
    key[strcspn(key, "\n")] = '\0'; // removing newline character from key

    // Check if the key has all unique characters
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (key[i] == key[j]) {
                printf("Error: Key must have all unique characters.\n");
                return 1;
            }
        }
    }

    ciphertext = encrypt(plaintext, key);
    printf("Encrypted text: %s\n", ciphertext);

    decryptedtext = decrypt(ciphertext, key);
    printf("Decrypted text: %s\n", decryptedtext);

    free(ciphertext);
    free(decryptedtext);

    return 0;
}

char* encrypt(char* plaintext, char* key) {
    char* ciphertext = (char*)malloc(strlen(plaintext) + 1);

    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (isupper(plaintext[i])) {
                ciphertext[i] = toupper(key[plaintext[i] - 'A']);
            } else {
                ciphertext[i] = tolower(key[plaintext[i] - 'a']);
            }
        } else {
            ciphertext[i] = plaintext[i]; // keep non-alphabetic characters unchanged
        }
    }

    ciphertext[strlen(plaintext)] = '\0';
    return ciphertext;
}

char* decrypt(char* ciphertext, char* key) {
    char* plaintext = (char*)malloc(strlen(ciphertext) + 1);

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (tolower(key[j]) == tolower(ciphertext[i])) {
                    if (isupper(ciphertext[i])) {
                        plaintext[i] = 'A' + j;
                    } else {
                        plaintext[i] = 'a' + j;
                    }
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i]; // keep non-alphabetic characters unchanged
        }
    }

    plaintext[strlen(ciphertext)] = '\0';
    return plaintext;
}

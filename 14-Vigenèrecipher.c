#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt the plaintext using the one-time pad version of the Vigenère cipher
void encryptVigenereOTP(char* plaintext, int* key, char* ciphertext) {
    int plaintextLen = strlen(plaintext);
    int keyLen = strlen(key);

    for (int i = 0; i < plaintextLen; i++) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
            int shift = key[i % keyLen];
            if (islower(ch)) {
                ciphertext[i] = 'a' + (ch - 'a' + shift) % 26;
            } else {
                ciphertext[i] = 'A' + (ch - 'A' + shift) % 26;
            }
        } else {
            ciphertext[i] = ch; // Keep non-alphabetic characters unchanged
        }
    }
    ciphertext[plaintextLen] = '\0';
}

// Function to decrypt the ciphertext using the one-time pad version of the Vigenère cipher
void decryptVigenereOTP(char* ciphertext, int* key, char* decryptedtext) {
    int ciphertextLen = strlen(ciphertext);
    int keyLen = strlen(key);

    for (int i = 0; i < ciphertextLen; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            int shift = key[i % keyLen];
            if (islower(ch)) {
                decryptedtext[i] = 'a' + (ch - 'a' - shift + 26) % 26;
            } else {
                decryptedtext[i] = 'A' + (ch - 'A' - shift + 26) % 26;
            }
        } else {
            decryptedtext[i] = ch; // Keep non-alphabetic characters unchanged
        }
    }
    decryptedtext[ciphertextLen] = '\0';
}

int main() {
    char plaintext[] = "sendmoremoney";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[strlen(plaintext) + 1];
    char decryptedtext[strlen(plaintext) + 1];

    // Encryption
    encryptVigenereOTP(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decryption
    decryptVigenereOTP(ciphertext, key, decryptedtext);
    printf("Decrypted Text: %s\n", decryptedtext);

    return 0;
}

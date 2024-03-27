#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// English letter frequencies (source: https://en.wikipedia.org/wiki/Letter_frequency)
const double englishFrequencies[ALPHABET_SIZE] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, // A-G
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, // H-N
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, // O-U
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074 // V-Z
};

// Function to decrypt the ciphertext using the specified key
void decryptAdditiveCipher(const char* ciphertext, int key, char* plaintext) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            char decryptedChar = ((ciphertext[i] - 'a' - key) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
            plaintext[i] = decryptedChar;
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[length] = '\0';
}

// Function to calculate the chi-square value for two frequency distributions
double calculateChiSquare(double* observed, double* expected) {
    double chiSquare = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (expected[i] > 0) {
            chiSquare += pow(observed[i] - expected[i], 2) / expected[i];
        }
    }
    return chiSquare;
}

// Function to perform a letter frequency attack on the additive cipher
void frequencyAttack(const char* ciphertext, int topPlaintexts) {
    double chiSquare[ALPHABET_SIZE];
    char plaintext[strlen(ciphertext) + 1];

    printf("Top %d possible plaintexts:\n", topPlaintexts);
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decryptAdditiveCipher(ciphertext, key, plaintext);
        double observedFrequencies[ALPHABET_SIZE] = {0};
        int totalLetters = 0;

        // Count letter frequencies in the plaintext
        for (int i = 0; plaintext[i]; i++) {
            if (isalpha(plaintext[i])) {
                totalLetters++;
                observedFrequencies[tolower(plaintext[i]) - 'a']++;
            }
        }

        // Normalize observed frequencies
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            observedFrequencies[i] /= totalLetters;
        }

        // Calculate chi-square value
        chiSquare[key] = calculateChiSquare(observedFrequencies, englishFrequencies);
    }

    // Print top plaintexts based on chi-square values
    for (int i = 0; i < topPlaintexts; i++) {
        int minIndex = 0;
        for (int j = 1; j < ALPHABET_SIZE; j++) {
            if (chiSquare[j] < chiSquare[minIndex]) {
                minIndex = j;
            }
        }
        decryptAdditiveCipher(ciphertext, minIndex, plaintext);
        printf("Key: %d, Plaintext: %s\n", minIndex, plaintext);
        chiSquare[minIndex] = INFINITY; // Mark the minimum as processed
    }
}

int main() {
    char ciphertext[] = "UDLULB JXPJLZ";

    // Perform a letter frequency attack and print the top possible plaintexts
    frequencyAttack(ciphertext, 10);

    return 0;
}

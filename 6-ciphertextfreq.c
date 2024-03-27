#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // Inverse doesn't exist
}

void decrypt(char* ciphertext, char* plaintext, int mostFreqLetter, int secondMostFreqLetter) {
    int a, b;
    int mostFreqIndex = mostFreqLetter - 'A';
    int secondMostFreqIndex = secondMostFreqLetter - 'A';
    
    // Finding 'a' using frequency analysis
    a = (mostFreqIndex - secondMostFreqIndex + ALPHABET_SIZE) % ALPHABET_SIZE;
    int inverse_a = modInverse(a, ALPHABET_SIZE);

    // Finding 'b' using the most frequent letter
    b = (inverse_a * (ciphertext[0] - 'A' - mostFreqIndex + ALPHABET_SIZE)) % ALPHABET_SIZE;

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int index = ciphertext[i] - base;
            index = (inverse_a * (index - b + ALPHABET_SIZE)) % ALPHABET_SIZE;
            plaintext[i] = (char)(index + base);
        } else {
            plaintext[i] = ciphertext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[1000], plaintext[1000];
    int mostFreqLetter, secondMostFreqLetter;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Finding the most frequent and second most frequent letters
    int frequency[ALPHABET_SIZE] = {0};
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int index = toupper(ciphertext[i]) - 'A';
            frequency[index]++;
        }
    }

    // Finding the most frequent letter
    int maxFreq = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxFreq) {
            maxFreq = frequency[i];
            mostFreqLetter = i + 'A';
        }
    }

    // Finding the second most frequent letter
    int secondMaxFreq = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > secondMaxFreq && frequency[i] < maxFreq) {
            secondMaxFreq = frequency[i];
            secondMostFreqLetter = i + 'A';
        }
    }

    decrypt(ciphertext, plaintext, mostFreqLetter, secondMostFreqLetter);

    printf("Plaintext: %s\n", plaintext);

    return 0;
}

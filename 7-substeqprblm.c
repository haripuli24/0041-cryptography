#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int frequency[ALPHABET_SIZE] = {0};
    char decodedAlphabet[ALPHABET_SIZE];
    char decodedText[strlen(ciphertext)];

    // Count frequency of characters
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            int index = toupper(ciphertext[i]) - 'A';
            frequency[index]++;
        }
    }

    // Find most frequent characters and map to English alphabet
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int maxFreq = 0;
        int maxFreqIndex = 0;
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (frequency[j] > maxFreq) {
                maxFreq = frequency[j];
                maxFreqIndex = j;
            }
        }
        decodedAlphabet[maxFreqIndex] = 'A' + i;
        frequency[maxFreqIndex] = 0; // Exclude this character from future consideration
    }

    // Decrypt ciphertext using decoded alphabet
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            int index = toupper(ciphertext[i]) - 'A';
            decodedText[i] = isupper(ciphertext[i]) ? decodedAlphabet[index] : tolower(decodedAlphabet[index]);
        } else {
            decodedText[i] = ciphertext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    decodedText[strlen(ciphertext)] = '\0';

    printf("Decrypted Text: %s\n", decodedText);

    return 0;
}

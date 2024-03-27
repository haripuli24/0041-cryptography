#include <stdio.h>
#include <stdlib.h>
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

char encrypt(char ch, int a, int b) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        int index = ch - base;
        index = (a * index + b) % ALPHABET_SIZE;
        return (char)(index + base);
    }
    return ch; // Return unchanged for non-alphabetic characters
}

char decrypt(char ch, int a, int b) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        int index = ch - base;
        int inverse_a = modInverse(a, ALPHABET_SIZE);
        index = (inverse_a * (index - b + ALPHABET_SIZE)) % ALPHABET_SIZE;
        return (char)(index + base);
    }
    return ch; // Return unchanged for non-alphabetic characters
}

int main() {
    int a, b;
    char plaintext[1000], ciphertext[1000], decryptedtext[1000];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the value of a: ");
    scanf("%d", &a);

    // Check if 'a' and 26 are coprime
    if (gcd(a, ALPHABET_SIZE) != 1) {
        printf("Error: The value of 'a' must be coprime with %d.\n", ALPHABET_SIZE);
        return 1;
    }

    printf("Enter the value of b: ");
    scanf("%d", &b);

    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = encrypt(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';

    printf("Ciphertext: %s\n", ciphertext);

    // Decrypting the ciphertext
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedtext[i] = decrypt(ciphertext[i], a, b);
    }
    decryptedtext[strlen(ciphertext)] = '\0';

    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

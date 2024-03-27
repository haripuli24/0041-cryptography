#include <stdio.h>

#define MATRIX_SIZE 2

// Function to perform matrix multiplication for Hill cipher
void matrixMultiply(int key[2][2], int message[2], int result[2]) {
    result[0] = (key[0][0] * message[0] + key[0][1] * message[1]) % 26;
    result[1] = (key[1][0] * message[0] + key[1][1] * message[1]) % 26;
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int key[MATRIX_SIZE][MATRIX_SIZE]) {
    return key[0][0] * key[1][1] - key[0][1] * key[1][0];
}

// Function to calculate the multiplicative inverse of a number modulo 26
int multiplicativeInverse(int a) {
    a = a % 26;
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1)
            return x;
    }
    return -1; // Inverse doesn't exist
}

// Function to calculate the inverse of a 2x2 matrix modulo 26
void inverse(int key[MATRIX_SIZE][MATRIX_SIZE], int inv[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(key);
    int invDet = multiplicativeInverse(det);
    int temp;

    // Calculate the adjugate matrix
    inv[0][0] = key[1][1];
    inv[1][1] = key[0][0];
    inv[0][1] = -key[0][1];
    inv[1][0] = -key[1][0];

    // Apply modular arithmetic to each element
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inv[i][j] = (inv[i][j] * invDet) % 26;
            if (inv[i][j] < 0) // Ensure positive result
                inv[i][j] += 26;
        }
    }
}

// Function to solve the Hill cipher encryption key given plaintext-ciphertext pairs
void solveKey(int plaintext[MATRIX_SIZE], int ciphertext[MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int inverseKey[MATRIX_SIZE][MATRIX_SIZE];
    int result[MATRIX_SIZE];

    inverse(key, inverseKey);
    matrixMultiply(inverseKey, ciphertext, result);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        key[i][0] = result[i] - plaintext[i];
        if (key[i][0] < 0)
            key[i][0] += 26;
    }

    matrixMultiply(inverseKey, plaintext, result);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        key[i][1] = result[i] - ciphertext[i];
        if (key[i][1] < 0)
            key[i][1] += 26;
    }
}

int main() {
    int plaintext[2] = {0, 1}; // Known plaintext
    int ciphertext[2] = {22, 19}; // Corresponding ciphertext

    int key[MATRIX_SIZE][MATRIX_SIZE];

    // Solve for the key
    solveKey(plaintext, ciphertext, key);

    // Print the key
    printf("Key Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}

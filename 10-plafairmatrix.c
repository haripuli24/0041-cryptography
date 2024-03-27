#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Function to remove spaces from a string
void removeSpaces(char* str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ')
            str[count++] = str[i];
    }
    str[count] = '\0';
}

// Function to prepare the message for encryption
void prepareMessage(char* message) {
    int length = strlen(message);
    for (int i = 0; i < length; i++) {
        if (!isalpha(message[i]))
            continue;
        message[i] = toupper(message[i]);
        if (message[i] == 'J')
            message[i] = 'I';
    }
}

// Function to find the position of a character in the Playfair matrix
void findPosition(char matrix[MATRIX_SIZE][MATRIX_SIZE], char ch, int* row, int* col) {
    if (ch == 'J')
        ch = 'I';
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt the message using the Playfair cipher
void encryptPlayfair(char* message, char matrix[MATRIX_SIZE][MATRIX_SIZE], char* ciphertext) {
    int length = strlen(message);
    int index = 0;

    for (int i = 0; i < length; i += 2) {
        char a = message[i];
        char b = (i + 1 < length) ? message[i + 1] : 'X'; // Append 'X' if message length is odd
        int rowA, colA, rowB, colB;

        findPosition(matrix, a, &rowA, &colA);
        findPosition(matrix, b, &rowB, &colB);

        if (rowA == rowB) { // Same row
            ciphertext[index++] = matrix[rowA][(colA + 1) % MATRIX_SIZE];
            ciphertext[index++] = matrix[rowB][(colB + 1) % MATRIX_SIZE];
        } else if (colA == colB) { // Same column
            ciphertext[index++] = matrix[(rowA + 1) % MATRIX_SIZE][colA];
            ciphertext[index++] = matrix[(rowB + 1) % MATRIX_SIZE][colB];
        } else { // Rectangle
            ciphertext[index++] = matrix[rowA][colB];
            ciphertext[index++] = matrix[rowB][colA];
        }
    }
    ciphertext[index] = '\0';
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };
    char ciphertext[100];

    removeSpaces(message);
    prepareMessage(message);
    encryptPlayfair(message, matrix, ciphertext);

    printf("Encrypted Message:\n%s\n", ciphertext);

    return 0;
}

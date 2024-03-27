#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void removeSpaces(char* str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ')
            str[count++] = str[i];
    }
    str[count] = '\0';
}

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

void decryptPlayfair(char* message, char* keyword) {
    char matrix[5][5];
    char key[ALPHABET_SIZE] = {0};
    int k = 0;

    // Construct the key
    for (int i = 0; i < strlen(keyword); i++) {
        if (keyword[i] == 'J')
            keyword[i] = 'I';
        if (!key[keyword[i] - 'A']) {
            key[keyword[i] - 'A'] = 1;
            matrix[k / 5][k % 5] = keyword[i];
            k++;
        }
    }

    // Fill the remaining matrix with the rest of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J')
            continue;
        if (!key[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            k++;
        }
    }

    // Decrypt the message
    for (int i = 0; i < strlen(message); i += 2) {
        char a = message[i];
        char b = message[i + 1];
        int rowA, colA, rowB, colB;

        // Find positions of characters in the matrix
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (matrix[row][col] == a) {
                    rowA = row;
                    colA = col;
                }
                if (matrix[row][col] == b) {
                    rowB = row;
                    colB = col;
                }
            }
        }

        // Same row, different columns
        if (rowA == rowB) {
            message[i] = matrix[rowA][(colA - 1 + 5) % 5];
            message[i + 1] = matrix[rowB][(colB - 1 + 5) % 5];
        }
        // Same column, different rows
        else if (colA == colB) {
            message[i] = matrix[(rowA - 1 + 5) % 5][colA];
            message[i + 1] = matrix[(rowB - 1 + 5) % 5][colB];
        }
        // Different rows and columns
        else {
            message[i] = matrix[rowA][colB];
            message[i + 1] = matrix[rowB][colA];
        }
    }
}

int main() {
    char message[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    char keyword[] = "PRESIDENT";

    removeSpaces(message);
    prepareMessage(message);
    decryptPlayfair(message, keyword);

    printf("Decrypted Message:\n%s\n", message);

    return 0;
}

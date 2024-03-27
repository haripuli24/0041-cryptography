#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE];

void generateKeyMatrix(char key[]) {
    int i, j, k;
    int len = strlen(key);
    char keyTable[26] = {0};
    int row = 0, col = 0;
    for (i = 0; i < len; i++) {
        if (keyTable[key[i] - 97] == 0) {
            matrix[row][col] = key[i];
            keyTable[key[i] - 97] = 1;
            col++;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
    for (i = 0; i < 26; i++) {
        if (keyTable[i] == 0) {
            matrix[row][col++] = (char)(i + 97);
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

void preprocess(char *text) {
    int i, len = strlen(text);
    for (i = 0; i < len; i++) {
        if (text[i] == 'j')
            text[i] = 'i';
    }
}

void prepareText(char *text) {
    int i, len = strlen(text);
    for (i = 0; i < len; i++) {
        if (!isalpha(text[i]))
            continue;
        if (text[i] == 'j')
            text[i] = 'i';
        if (tolower(text[i]) == tolower(text[i + 1])) {
            memmove(&text[i + 1], &text[i], strlen(text) - i + 1);
            text[i + 1] = 'x';
        }
    }
}

void encrypt(char *text) {
    int i, j;
    char a, b;
    int row1, row2, col1, col2;
    for (i = 0; i < strlen(text); i += 2) {
        a = text[i];
        b = text[i + 1];
        for (j = 0; j < SIZE; j++) {
            if (strchr(matrix[j], a)) {
                row1 = j;
                col1 = (int)(strchr(matrix[j], a) - matrix[j]);
            }
            if (strchr(matrix[j], b)) {
                row2 = j;
                col2 = (int)(strchr(matrix[j], b) - matrix[j]);
            }
        }
        if (row1 == row2) {
            text[i] = matrix[row1][(col1 + 1) % SIZE];
            text[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            text[i] = matrix[(row1 + 1) % SIZE][col1];
            text[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            text[i] = matrix[row1][col2];
            text[i + 1] = matrix[row2][col1];
        }
    }
}

int main() {
    char key[100], text[100];
    
    printf("Enter the key: ");
    scanf("%s", key);
    
    printf("Enter the plaintext: ");
    scanf("%s", text);
    
    preprocess(text);
    prepareText(text);
    
    generateKeyMatrix(key);
    encrypt(text);
    
    printf("Encrypted text: %s\n", text);
    
    return 0;
}

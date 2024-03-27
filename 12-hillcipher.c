#include <stdio.h>
#include <ctype.h>

// Function to prepare the message for encryption/decryption
void prepareMessage(char* message) {
    for (int i = 0; message[i]; i++) {
        if (isalpha(message[i]))
            message[i] = toupper(message[i]);
    }
}

// Function to perform matrix multiplication for Hill cipher
void matrixMultiply(int key[2][2], int message[2], int result[2]) {
    result[0] = (key[0][0] * message[0] + key[0][1] * message[1]) % 26;
    result[1] = (key[1][0] * message[0] + key[1][1] * message[1]) % 26;
}

// Function to perform encryption or decryption
void hillCipher(char* message, int key[2][2], char* result) {
    prepareMessage(message);

    int length = 0;
    while (message[length])
        length++;

    for (int i = 0; i < length; i += 2) {
        int msg[2] = {message[i] - 'A', (i + 1 < length) ? message[i + 1] - 'A' : 0};
        int res[2];

        matrixMultiply(key, msg, res);

        result[i] = res[0] + 'A';
        result[i + 1] = res[1] + 'A';
    }
    result[length] = '\0';
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight oclock";
    int key[2][2] = {{9, 4}, {5, 7}};
    char ciphertext[100];
    char decryptedtext[100];

    // Encryption
    hillCipher(message, key, ciphertext);
    printf("Encrypted Message:\n%s\n", ciphertext);

    // Decryption
    hillCipher(ciphertext, key, decryptedtext);
    printf("Decrypted Message:\n%s\n", decryptedtext);

    return 0;
}

#include <stdio.h>
#include <string.h>

void caesarCipher(char *text, int shift);

int main() {
    char text[100];
    int shift;

    // Input text from the user
    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);

    // Input shift value
    printf("Enter the shift value (1 to 25): ");
    scanf("%d", &shift);

    // Encrypt the text
    caesarCipher(text, shift);

    // Output the encrypted text
    printf("Encrypted text: %s\n", text);

    return 0;
}

void caesarCipher(char *text, int shift) {
    int i;

    // Iterate through each character in the text
    for (i = 0; i < strlen(text); i++) {
        char c = text[i];

        // Encrypt only alphabetic characters
        if (c >= 'A' && c <= 'Z') {
            c = ((c - 'A' + shift) % 26) + 'A'; // Shift uppercase letters
        } else if (c >= 'a' && c <= 'z') {
            c = ((c - 'a' + shift) % 26) + 'a'; // Shift lowercase letters
        }

        text[i] = c; // Replace the character with its encrypted counterpart
    }
}

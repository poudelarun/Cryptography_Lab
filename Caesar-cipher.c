//Caeser Cipher
#include <stdio.h>
#include <string.h>

void caesar_encrypt(char message[], int key) {
    int i;
    char ch;

    for (i = 0; message[i] != '\0'; i++) {
        ch = message[i];

        if (ch >= 'a' && ch <= 'z') {
            ch = ch + key;

            if (ch > 'z') {
                ch = ch - 'z' + 'a' - 1;
            }

            message[i] = ch;
        }
    }
}

void caesar_decrypt(char message[], int key) {
    int i;
    char ch;

    for (i = 0; message[i] != '\0'; i++) {
        ch = message[i];

        if (ch >= 'a' && ch <= 'z') {
            ch = ch - key;

            if (ch < 'a') {
                ch = ch + 'z' - 'a' + 1;
            }

            message[i] = ch;
        }
    }
}

int main() {
    char message[100];
    int key;
    int choice;

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter a key (positive integer): ");
    scanf("%d", &key);

    printf("Choose an option:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            caesar_encrypt(message, key);
            printf("Encrypted message: %s\n", message);
            break;
        case 2:
            caesar_decrypt(message, key);
            printf("Decrypted message: %s\n", message);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

// Function to encrypt a message using Hill Cipher
void encrypt(int key[][2], char message[], char encrypted[]) {
    int messageLen = strlen(message);
    int keySize = 2;

    for (int i = 0; i < messageLen; i += keySize) {
        int vector[keySize];
        int encryptedVector[keySize];

        for (int j = 0; j < keySize; j++) {
            vector[j] = message[i + j] - 'A';
        }

        for (int j = 0; j < keySize; j++) {
            encryptedVector[j] = 0;
            for (int k = 0; k < keySize; k++) {
                encryptedVector[j] += key[j][k] * vector[k];
            }
            encryptedVector[j] %= MOD;
            encrypted[i + j] = encryptedVector[j] + 'A';
        }
    }
    encrypted[messageLen] = '\0';
}

// Function to decrypt a message using Hill Cipher
void decrypt(int key[][2], char encrypted[], char decrypted[]) {
    int keySize = 2;
    int keyInverse[2][2];

    // Calculate the modular inverse of the determinant
    int determinant = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
    int detInverse = -1;

    for (int i = 1; i < MOD; i++) {
        if ((determinant * i) % MOD == 1) {
            detInverse = i;
            break;
        }
    }

    // Calculate the inverse key matrix
    keyInverse[0][0] = key[1][1] * detInverse % MOD;
    keyInverse[0][1] = (-key[0][1]) * detInverse % MOD;
    keyInverse[1][0] = (-key[1][0]) * detInverse % MOD;
    keyInverse[1][1] = key[0][0] * detInverse % MOD;

    int encryptedLen = strlen(encrypted);

    for (int i = 0; i < encryptedLen; i += keySize) {
        int vector[keySize];
        int decryptedVector[keySize];

        for (int j = 0; j < keySize; j++) {
            vector[j] = encrypted[i + j] - 'A';
        }

        for (int j = 0; j < keySize; j++) {
            decryptedVector[j] = 0;
            for (int k = 0; k < keySize; k++) {
                decryptedVector[j] += keyInverse[j][k] * vector[k];
            }
            decryptedVector[j] = (decryptedVector[j] + MOD) % MOD;
            decrypted[i + j] = decryptedVector[j] + 'A';
        }
    }
    decrypted[encryptedLen] = '\0';
}

int main() {
    int key[2][2] = {{2, 3}, {3, 6}};
    char message[100];
    char encrypted[100];
    char decrypted[100];
    printf("***Hill Cipher***\n");
    printf("Enter a message (uppercase): ");
    scanf("%s", message);

    // Encryption
    encrypt(key, message, encrypted);
    printf("Encrypted: %s\n", encrypted);

    // Decryption
    decrypt(key, encrypted, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}

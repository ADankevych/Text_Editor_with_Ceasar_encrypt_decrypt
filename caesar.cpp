#include <iostream>

extern "C" {
char* encrypt(char* rawText, int key) {
    char *encryptedText = new char[strlen(rawText) + 1];
    for (int i = 0; i < strlen(rawText); i++) {
        char element = rawText[i];
        if (element >= 'a' && element <= 'z') {
            element = element + key;
            while (element > 'z') {
                element = element - 'z' + 'a' - 1;
            }
            encryptedText[i] = element;
        } else if (element >= 'A' && element <= 'Z') {
            element = element + key;
            while (element > 'Z') {
                element = element - 'Z' + 'A' - 1;
            }
            encryptedText[i] = element;
        } else {
            encryptedText[i] = element;
        }
    }
    encryptedText[strlen(rawText)] = '\0';

    return encryptedText;
}

char* decrypt(char* encryptedText, int key) {
    char *decryptedText = new char[strlen(encryptedText) + 1];
    for (int i = 0; i < strlen(encryptedText); i++) {
        char element = encryptedText[i];
        if (element >= 'a' && element <= 'z') {
            element = element - key;
            if (element < 'a') {
                element = element + 'z' - 'a' + 1;
            }
            decryptedText[i] = element;
        } else if (element >= 'A' && element <= 'Z') {
            element = element - key;
            if (element < 'A') {
                element = element + 'Z' - 'A' + 1;
            }
            decryptedText[i] = element;
        } else {
            decryptedText[i] = element;
        }
    }
    decryptedText[strlen(encryptedText)] = '\0';

    return decryptedText;
}
}
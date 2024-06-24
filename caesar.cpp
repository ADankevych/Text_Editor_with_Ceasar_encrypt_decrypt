#include <iostream>

extern "C" {
char* encrypt(char* rawText, int key) {
    key = key % 26;
    char *encryptedText = new char[strlen(rawText) + 1];
    for (int i = 0; i < strlen(rawText); i++) {
        char element = rawText[i];
        if (element >= 'a' && element <= 'z') {
            int counter = element + key;
            if (counter > 122) {  // 122 ASCII 'z', проблема з тим що виходило за межі таблтці ASCII
                element = counter - 26;
            }
        } else if (element >= 'A' && element <= 'Z') {
            element = element + key;
            if (element > 'Z') {
                element = element - 26;
            }
        }
        encryptedText[i] = element;
    }
    encryptedText[strlen(rawText)] = '\0';

    return encryptedText;
}

char* decrypt(char* encryptedText, int key) {
    key = key % 26;
    char *decryptedText = new char[strlen(encryptedText) + 1];
    for (int i = 0; i < strlen(encryptedText); i++) {
        char element = encryptedText[i];
        if (element >= 'a' && element <= 'z') {
            element = element - key;
            if (element < 'a') {
                element = element + 26;
            }
        } else if (element >= 'A' && element <= 'Z') {
            element = element - key;
            if (element < 'A') {
                element = element + 26;
            }
        }
        decryptedText[i] = element;
    }
    decryptedText[strlen(encryptedText)] = '\0';

    return decryptedText;
}
}
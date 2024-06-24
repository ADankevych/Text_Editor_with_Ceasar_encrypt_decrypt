#include <iostream>
#include "caesar.cpp"
#include <dlfcn.h>
using namespace std;

typedef char* (*encrypt_ptr_t)(char*, int);
typedef char* (*decrypt_ptr_t)(char*, int);

void RewriteFile();
int Menu(int optionNumber);

char *globalCopiedText = nullptr;
char *techFilesForSave [4] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt"};
int functions [4] = {0, 0, 0, 0};
int currentFileIndex = 0;

FILE *techFile;
FILE *techSaveFile;
FILE *savingFile;
FILE *loadingFile;

class Append {
public:

    static void AppendText() {
        cout<<"Enter text to append: \n";
        techFile = fopen("file.txt", "a");
        char userInput;
        getchar();
        while(true) {
            userInput = getchar();
            if (userInput == '\n') {
                break;
            }
            fprintf(techFile, "%c", userInput);
        }
        fclose(techFile);
    }

    static void NewLine() {
        cout<<"New line is started \n";
        techFile = fopen("file.txt", "a");
        fprintf(techFile, "\n");
        fclose(techFile);
    }

    static void CurrentText() {
        techSaveFile = fopen(techFilesForSave[currentFileIndex], "r");
        char c;
        while ((c = getc(techSaveFile)) != EOF) {
            cout<<c;
        }
        cout<<endl;
        fclose(techSaveFile);
    }

};

class SaveLoad {
public:

    static void SaveTo() {
        cout<<"Enter the file name for saving (not more 20 symbols): \n";
        char filePath[21];
        cin>>filePath;

        savingFile = fopen(filePath, "a");
        techFile = fopen("file.txt", "r");
        char symbol;
        while (true) {
            symbol = fgetc(techFile);
            if (symbol == EOF) {
                break;
            }
            fputc(symbol, savingFile);
        }
        fclose(savingFile);
        fclose(techFile);

        techFile = fopen("file.txt", "w"); // просто очистити файл
        fclose(techFile);
    }

    static void LoadFrom() {
        cout<<"Enter the file name for loading: \n";
        char filePath[21];
        cin>>filePath;
        techFile = fopen("file.txt", "a");
        loadingFile = fopen(filePath, "r");
        char symbol;
        while (true) {
            symbol = fgetc(loadingFile);
            if (symbol == EOF) {
                break;
            }
            fputc(symbol, techFile);
        }
        fclose(loadingFile);
        fclose(techFile);
    }
};

class DeleteCopyCutPaste {
public:
    static void Delete(){
        cout<<"Choose line, index and number of symbols: \n";
        int line;
        int index;
        int numberOfSymbols;
        cin>>line>>index>>numberOfSymbols;

        techFile = fopen("file.txt", "r");
        long fileSize = 0;
        char symbol;
        while ((symbol = fgetc(techFile)) != EOF) {
            fileSize++;
        }
        fclose(techFile);

        char *fileContent = (char *) malloc((fileSize + 1) * sizeof(char));
        techFile = fopen("file.txt", "r");
        fread(fileContent, 1, fileSize, techFile);
        fileContent[fileSize] = '\0';
        fclose(techFile);

        int lineCounter = 0;
        int indexCounter = 0;
        int counter1 = 0;

        while (fileContent[counter1] != '\0') {
            if (lineCounter == line && indexCounter == index) {
                break;
            }
            if (fileContent[counter1] == '\n') {
                lineCounter++;
                indexCounter = 0;
            } else {
                indexCounter++;
            }
            counter1++;
        }

        int newFileSize = fileSize - numberOfSymbols;
        char *newFileContent = (char *) malloc((newFileSize + 1) * sizeof(char));
        int counter2 = 0;
        for (int i = 0; i < counter1; i++) {
            newFileContent[counter2] = fileContent[i];
            counter2++;
        }
        for (int i = counter1 + numberOfSymbols; i < fileSize; i++) {
            newFileContent[counter2] = fileContent[i];
            counter2++;
        }
        newFileContent[newFileSize] = '\0';

        techFile = fopen("file.txt", "w");
        fputs(newFileContent, techFile);
        fclose(techFile);

        free(fileContent);
        free(newFileContent);
    }

    static void Copy(){
        cout<<"Choose line, index and number of symbols: \n";
        int line;
        int index;
        int numberOfSymbols;
        cin>>line>>index>>numberOfSymbols;

        techFile = fopen("file.txt", "r");
        long fileSize = 0;
        char symbol;
        while ((symbol = fgetc(techFile)) != EOF) {
            fileSize++;
        }
        fclose(techFile);

        char *fileContent = (char *) malloc((fileSize + 1) * sizeof(char));
        techFile = fopen("file.txt", "r");
        fread(fileContent, 1, fileSize, techFile);
        fileContent[fileSize] = '\0';
        fclose(techFile);

        int lineCounter = 0;
        int indexCounter = 0;
        int counter1 = 0;

        while (fileContent[counter1] != '\0') {
            if (lineCounter == line && indexCounter == index) {
                break;
            }
            if (fileContent[counter1] == '\n') {
                lineCounter++;
                indexCounter = 0;
            } else {
                indexCounter++;
            }
            counter1++;
        }

        char *copiedText = (char *) malloc((numberOfSymbols + 1) * sizeof(char));
        int counter2 = 0;
        for (int i = counter1; i < counter1 + numberOfSymbols; i++) {
            copiedText[counter2] = fileContent[i];
            counter2++;
        }
        copiedText[numberOfSymbols] = '\0';

        if (globalCopiedText != nullptr) {
            free(globalCopiedText);
            globalCopiedText = nullptr;
        }

        globalCopiedText = (char *) realloc(globalCopiedText, strlen(copiedText) + 1);
        strcpy(globalCopiedText, copiedText);

        free(fileContent);
        free(copiedText);
    }

    static void Cut(){
        cout<<"Choose line, index and number of symbols: \n";
        int line;
        int index;
        int numberOfSymbols;
        cin>>line>>index>>numberOfSymbols;

        techFile = fopen("file.txt", "r");
        long fileSize = 0;
        char symbol;
        while ((symbol = fgetc(techFile)) != EOF) {
            fileSize++;
        }
        fclose(techFile);

        char *fileContent = (char *) malloc((fileSize + 1) * sizeof(char));
        techFile = fopen("file.txt", "r");
        fread(fileContent, 1, fileSize, techFile);
        fileContent[fileSize] = '\0';
        fclose(techFile);

        int lineCounter = 0;
        int indexCounter = 0;
        int counter1 = 0;

        while (fileContent[counter1] != '\0') {
            if (lineCounter == line && indexCounter == index) {
                break;
            }
            if (fileContent[counter1] == '\n') {
                lineCounter++;
                indexCounter = 0;
            } else {
                indexCounter++;
            }
            counter1++;
        }

        int newFileSize = fileSize - numberOfSymbols;
        char *newFileContent = (char *) malloc((newFileSize + 1) * sizeof(char));
        int counter2 = 0;
        for (int i = 0; i < counter1; i++) {
            newFileContent[counter2] = fileContent[i];
            counter2++;
        }

        if (globalCopiedText != nullptr) {
            free(globalCopiedText);
            globalCopiedText = nullptr;
        }

        char *copiedText = (char *) malloc((numberOfSymbols + 1) * sizeof(char));
        int counter3 = 0;
        for (int i = counter1; i < counter1 + numberOfSymbols; i++) {
            copiedText[counter3] = fileContent[i];
            counter3++;
        }
        copiedText[numberOfSymbols] = '\0';

        globalCopiedText = (char *) realloc(globalCopiedText, strlen(copiedText) + 1);
        strcpy(globalCopiedText, copiedText);

        for (int i = counter1 + numberOfSymbols; i < fileSize; i++) {
            newFileContent[counter2] = fileContent[i];
            counter2++;
        }
        newFileContent[newFileSize] = '\0';

        techFile = fopen("file.txt", "w");
        fputs(newFileContent, techFile);
        fclose(techFile);

        free(fileContent);
        free(newFileContent);
        free(copiedText);
    }

    static void Paste(){
        cout<<"Enter the line and index to paste: \n";
        int line;
        int index;
        cin>>line>>index;

        techFile = fopen("file.txt", "r");
        long fileSize = 0;
        char symbol;
        while ((symbol = fgetc(techFile)) != EOF) {
            fileSize++;
        }
        fclose(techFile);

        char *fileContent = (char *) malloc((fileSize + 1) * sizeof(char));
        techFile = fopen("file.txt", "r");
        fread(fileContent, 1, fileSize, techFile);
        fileContent[fileSize] = '\0';
        fclose(techFile);

        int lineCounter = 0;
        int indexCounter = 0;
        int counter1 = 0;

        while (fileContent[counter1] != '\0') {
            if (lineCounter == line && indexCounter == index) {
                break;
            }
            if (fileContent[counter1] == '\n') {
                lineCounter++;
                indexCounter = 0;
            } else {
                indexCounter++;
            }
            counter1++;
        }

        int newFileSize = fileSize + strlen(globalCopiedText);
        char *newFileContent = (char *) malloc((newFileSize + 1) * sizeof(char));
        int counter2 = 0;
        for (int i = 0; i < counter1; i++) {
            newFileContent[counter2] = fileContent[i];
            counter2++;
        }
        for (int i = 0; i < strlen(globalCopiedText); i++) {
            newFileContent[counter2] = globalCopiedText[i];
            counter2++;
        }
        for (int i = counter1; i < fileSize; i++) {
            newFileContent[counter2] = fileContent[i];
            counter2++;
        }
        newFileContent[newFileSize] = '\0';

        techFile = fopen("file.txt", "w");
        fputs(newFileContent, techFile);
        fclose(techFile);

        free(fileContent);
        free(newFileContent);
    }
};

class InsertReplaceSearch {
public:
    static void InsertText() {
        cout<<"Choose line and index to insert text: \n";
        int line;
        int index;
        cin>>line>>index;
        getchar();

        techFile = fopen("file.txt", "r");
        long fileSize = 0;
        char symbol;
        while ((symbol = fgetc(techFile)) != EOF) {
            fileSize++;
        }
        fclose(techFile);

        char *fileContent = (char *) malloc((fileSize+1) * sizeof(char));
        techFile = fopen("file.txt", "r");
        fread(fileContent, 1, fileSize, techFile);
        fileContent[fileSize] = '\0';
        fclose(techFile);

        int lineCounter = 0;
        int indexCounter = 0;
        int counter1 = 0;
        while (fileContent[counter1] != '\0') {
            if (lineCounter == line && indexCounter == index) {
                break;
            }
            if (fileContent[counter1] == '\n') {
                lineCounter++;
                indexCounter = 0;
            } else {
                indexCounter++;
            }
            counter1++;
        }

        cout<<"Enter the text to insert: \n";
        char *userInput = (char *) malloc(100 * sizeof(char));
        fgets(userInput, 100, stdin);
        int userInputSize = strlen(userInput);

        if (userInput[userInputSize - 1] == '\n') {
            userInput[userInputSize - 1] = '\0';
            userInputSize--;
        }

        int newFileSize = fileSize + userInputSize;
        char *newFileContent = (char *)malloc((newFileSize + 1) * sizeof(char));
        int counter2 = 0;
        for (int i = 0; i < counter1; i++) {
            newFileContent[counter2] = fileContent[i];
            counter2++;
        }
        for (int i = 0; i < userInputSize; i++) {
            newFileContent[counter2] = userInput[i];
            counter2++;
        }
        for (int i = counter1; i < fileSize; i++) {
            newFileContent[counter2] = fileContent[i];
            counter2++;
        }
        newFileContent[newFileSize] = '\0';

        techFile = fopen("file.txt", "w");
        fputs(newFileContent, techFile);
        fclose(techFile);

        free(fileContent);
        free(userInput);
        free(newFileContent);
    }

    static void Replace(){
        cout<<"Choose line and index: \n";
        int line;
        int index;
        cin>>line>>index;
        getchar();

        techFile = fopen("file.txt", "r");
        long fileSize = 0;
        char symbol;
        while ((symbol = fgetc(techFile)) != EOF) {
            fileSize++;
        }
        fclose(techFile);

        char *fileContent = (char *) malloc((fileSize + 1) * sizeof(char));
        techFile = fopen("file.txt", "r");
        fread(fileContent, 1, fileSize, techFile);
        fileContent[fileSize] = '\0';
        fclose(techFile);

        int lineCounter = 0;
        int indexCounter = 0;
        int counter1 = 0;
        while (fileContent[counter1] != '\0') {
            if (lineCounter == line && indexCounter == index) {
                break;
            }
            if (fileContent[counter1] == '\n') {
                lineCounter++;
                indexCounter = 0;
            } else {
                indexCounter++;
            }
            counter1++;
        }

        cout<<"Enter the text to replace: \n";
        char *userInput = (char *) malloc(100 * sizeof(char));
        fgets(userInput, 100, stdin);
        int userInputSize = strlen(userInput);

        if (userInput[userInputSize - 1] == '\n') {
            userInput[userInputSize - 1] = '\0';
            userInputSize--;
        }

        int newFileSize = fileSize - 1 + userInputSize;
        char *newFileContent = (char *) malloc((newFileSize + 1) * sizeof(char));
        int counter2 = 0;
        for (int i = 0; i < counter1; i++) {
            newFileContent[counter2] = fileContent[i];
            counter2++;
        }
        for (int i = 0; i < userInputSize; i++) {
            newFileContent[counter2] = userInput[i];
            counter2++;
        }
        for (int i = counter2; i < fileSize; i++) {
            newFileContent[i] = fileContent[i];
        }

        newFileContent[newFileSize] = '\0';

        techFile = fopen("file.txt", "w");
        fputs(newFileContent, techFile);
        fclose(techFile);

        free(fileContent);
        free(userInput);
        free(newFileContent);
    }

    static void Search() {
        cout<<"Enter the text to search: \n";
        getchar();
        char *searchText = (char *) malloc(100 * sizeof(char));
        fgets(searchText, 100, stdin);
        int lenInput = strlen(searchText);
        if (searchText[lenInput - 1] == '\n') {
            searchText[lenInput - 1] = '\0';
            lenInput--;
        }

        techFile = fopen("file.txt", "r");
        long fileSize = 0;
        char symbol;
        while ((symbol = fgetc(techFile)) != EOF) {
            fileSize++;
        }
        fclose(techFile);

        techFile = fopen("file.txt", "r");
        char *fileContent = (char *) malloc((fileSize + 1) * sizeof(char));

        fread(fileContent, 1, fileSize, techFile);
        fileContent[fileSize] = '\0';

        char *lineBuffer = (char *) malloc(100 * sizeof(char));
        int lineNumber = 0;
        int currentIndex = 0;
        char *pos = strstr(fileContent, searchText);
        if (pos != NULL) {
            int index = pos - fileContent;
            for (int i = 0; i < index; i++) {
                if (fileContent[i] == '\n') {
                    lineNumber++;
                    currentIndex = 0;
                }
                currentIndex++;
            }
            cout<<lineNumber + 1<<currentIndex + 1<<endl;
        }

        free(searchText);
        free(fileContent);
        free(lineBuffer);
        fclose(techFile);
    }

};

class UndoRedo {
public:
    static void Undo() {
        int index;
        if (currentFileIndex == 0){
            index = 1;
        }
        else if (currentFileIndex == 1){
            index = 2;
        }
        else if (currentFileIndex == 2){
            index = 3;
        }
        else if (currentFileIndex == 3){
            index = 0;
        }

        techFile = fopen("file.txt", "w");
        techSaveFile = fopen(techFilesForSave[index], "r");
        char c;
        while ((c = getc(techSaveFile)) != EOF) {
            putc(c, techFile);
        }
        fclose(techFile);
        fclose(techSaveFile);
    }

    static void Redo() {
        if (currentFileIndex == 0){
            Menu(functions[currentFileIndex = 1]);
            Menu(functions[currentFileIndex = 2]);
            Menu(functions[currentFileIndex = 3]);
        }
        else if (currentFileIndex == 1){
            Menu(functions[currentFileIndex = 2]);
            Menu(functions[currentFileIndex = 3]);
            Menu(functions[currentFileIndex = 0]);
        }
        else if (currentFileIndex == 2){
            Menu(functions[currentFileIndex = 3]);
            Menu(functions[currentFileIndex = 0]);
            Menu(functions[currentFileIndex = 1]);
        }
        else if (currentFileIndex == 3){
            Menu(functions[currentFileIndex = 0]);
            Menu(functions[currentFileIndex = 1]);
            Menu(functions[currentFileIndex = 2]);
        }
    }

};

class CaesarCipher {
public:
    static int EncryptText(){
        void* handle = dlopen("./caesar.so", RTLD_LAZY);
        if (handle == nullptr) {
            cout << "Lib not found" << endl;
            return -1;
        }
        int key;
        encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)dlsym(handle, "encrypt");

        cout << "Do you want to encrypt new text or previously saved text? (n/s)\n";
        char answer;
        cin>>answer;
        char* encryptedText;
        if (answer == 'n') {
            char rawText[100];
            cout << "Enter the text you want to encrypt, and key: " << endl;
            cin.getline(rawText, 100);
            cin >> key;
            cin.ignore();
            encryptedText = encrypt_ptr(rawText, key);
            cout << "Encrypted text: " << encryptedText << endl;
        }
        else if (answer == 's'){
            techFile = fopen("file.txt", "r");
            cout << "Enter the key: " << endl;
            cin >> key;
            cin.ignore();

            techFile = fopen("file.txt", "r");
            long fileSize = 0;
            char symbol;
            while ((symbol = fgetc(techFile)) != EOF) {
                fileSize++;
            }
            fclose(techFile);
            char *fileContent = (char *) malloc((fileSize + 1) * sizeof(char));
            techFile = fopen("file.txt", "r");
            fread(fileContent, 1, fileSize, techFile);
            fileContent[fileSize] = '\0';
            fclose(techFile);

            encryptedText = encrypt_ptr(fileContent, key);
            cout << "Encrypted text: " << encryptedText << endl;

            free(fileContent);
        }
        cout<< "Do you want to save the encrypted text? (y/n)\n";
        cin>>answer;
        if (answer == 'y'){
            cout<<"Do you want append the text or rewrite it? (a/r)\n";
            cin>>answer;
            if (answer == 'a'){
                techFile = fopen("file.txt", "a");
                fprintf(techFile, "%s", encryptedText);
                fclose(techFile);
                cout<<"The text was saved\n";
            }
            else if (answer == 'r'){
                techFile = fopen("file.txt", "w");
                fprintf(techFile, "%s", encryptedText);
                fclose(techFile);
                cout<<"The text was saved\n";
            }
            cout<<"Do you want to add a key to the text? (y/n)\n";
            cin>>answer;
            if (answer == 'y'){
                techFile = fopen("file.txt", "a");
                fprintf(techFile, "%d", key);
            }
        }
        free(encryptedText);
        dlclose(handle);
    }

    static int DecryptText(){
        void* handle = dlopen("./caesar.so", RTLD_LAZY);
        if (handle == nullptr) {
            cout << "Lib not found" << endl;
            return -1;
        }

        decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)dlsym(handle, "decrypt");
        int key;
        cout << "Do you want to decrypt new text or previously saved text? (n/s)\n";
        char answer;
        cin>>answer;
        char* decryptedText;
        if (answer == 'n') {
            cout << "Enter the text you want to decrypt, and key: " << endl;
            char textForDecrypt[100];
            cin.getline(textForDecrypt, 100);
            cin >> key;
            cin.ignore();
            decryptedText = decrypt_ptr(textForDecrypt, key);
            cout << "Decrypted text: " << decryptedText << endl;
        }
        else if (answer == 's'){
            techFile = fopen("file.txt", "r");
            cout << "Enter the key: " << endl;
            cin >> key;
            cin.ignore();

            techFile = fopen("file.txt", "r");
            long fileSize = 0;
            char symbol;
            while ((symbol = fgetc(techFile)) != EOF) {
                fileSize++;
            }
            fclose(techFile);
            char *fileContent = (char *) malloc((fileSize + 1) * sizeof(char));
            techFile = fopen("file.txt", "r");
            fread(fileContent, 1, fileSize, techFile);
            fileContent[fileSize] = '\0';
            fclose(techFile);

            decryptedText = decrypt_ptr(fileContent, key);
            cout << "Decrypted text: " << decryptedText << endl;

            free(fileContent);
        }

        cout<< "Do you want to save the decrypted text? (y/n)\n";
        cin>>answer;
        if (answer == 'y'){
            cout<<"Do you want append the text or rewrite it? (a/r)\n";
            cin>>answer;
            if (answer == 'a'){
                techFile = fopen("file.txt", "a");
                fprintf(techFile, "%s", decryptedText);
                fclose(techFile);
                cout<<"The text was saved\n";
            }
            else if (answer == 'r'){
                techFile = fopen("file.txt", "w");
                fprintf(techFile, "%s", decryptedText);
                fclose(techFile);
                cout<<"The text was saved\n";
            }
            cout<<"Do you want to add a key to the text? (y/n)\n";
            cin>>answer;
            if (answer == 'y'){
                techFile = fopen("file.txt", "a");
                fprintf(techFile, "%d", key);
            }
        }
        free(decryptedText);
        dlclose(handle);
    }

    static int EncryptFile(){}

    static int DecryptFile(){}
};

void RewriteFile() {
    techFile = fopen("file.txt", "r");
    techSaveFile = fopen(techFilesForSave[currentFileIndex], "w");
    char c;
    while ((c = getc(techFile)) != EOF) {
        putc(c, techSaveFile);
    }
    fclose(techFile);
    fclose(techSaveFile);
}

int Menu(int optionNumber){
    if (currentFileIndex == 4){
        currentFileIndex = 0;
    }
    RewriteFile();
    switch (optionNumber) {
        case 0:
            free(globalCopiedText);
            globalCopiedText = nullptr;
            return 0;
        case 1:
            Append::AppendText();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 2:
            Append::NewLine();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 3:
            SaveLoad::SaveTo();
            RewriteFile();
            break;
        case 4:
            SaveLoad::LoadFrom();
            RewriteFile();
            break;
        case 5:
            Append::CurrentText();
            RewriteFile();
            break;
        case 6:
            InsertReplaceSearch::InsertText();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 7:
            InsertReplaceSearch::Search();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 8:
            DeleteCopyCutPaste::Delete();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 9:
            DeleteCopyCutPaste::Copy();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 10:
            DeleteCopyCutPaste::Cut();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 11:
            DeleteCopyCutPaste::Paste();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 12:
            UndoRedo::Undo();
            RewriteFile();
            functions[currentFileIndex] = optionNumber;
            currentFileIndex++;
            break;
        case 13:
            UndoRedo::Redo();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 14:
            InsertReplaceSearch::Replace();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 15:
            CaesarCipher::EncryptText();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 16:
            CaesarCipher::DecryptText();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 17:
            CaesarCipher::EncryptFile();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        case 18:
            CaesarCipher::DecryptFile();
            functions[currentFileIndex] = optionNumber;
            RewriteFile();
            currentFileIndex++;
            break;
        default:
            cout<<"The command is not implemented\n";
            break;
    }
}

int main()
{
    cout<<"Hello, World!\n";

    techFile = fopen("file.txt", "w");
    fclose(techFile);
    techSaveFile = fopen("file1.txt", "w");
    fclose(techSaveFile);
    techSaveFile = fopen("file2.txt", "w");
    fclose(techSaveFile);
    techSaveFile = fopen("file3.txt", "w");
    fclose(techSaveFile);
    techSaveFile = fopen("file4.txt", "w");
    fclose(techSaveFile);

    cout<<"0 - exit \n"
        <<"1 - Append text symbols to the end \n"
        <<"2 - Start the new line \n"
        <<"3 - Use files to saving the information \n"
        <<"4 - Use files to loading the information \n"
        <<"5 - Print the current text to console \n"
        <<"6 - Insert the text by line and symbol index \n"
        <<"7 - Search \n"
        <<"8 - Delete \n"
        <<"9 - Copy \n"
        <<"10 - Cut \n"
        <<"11 - Paste \n"
        <<"12 - Undo \n"
        <<"13 - Redo \n"
        <<"14 - Replace \n"
        <<"15 - Encrypt \n"
        <<"16 - Decrypt \n"
        <<"17 - Encrypt file \n"
        <<"18 - Decrypt file \n";


    int optionNumber;
    while (true) {
        cout<<"Please, choose the command\n";
        cin>>optionNumber;
        if (Menu(optionNumber) == 0){
            break;
        }
    }
    return 0;
}

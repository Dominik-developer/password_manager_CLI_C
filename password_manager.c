#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "password_manager.h"


// main program functions
void addCredentials() {

    FILE *pFile = fopen("credentials.txt", "a");

    if(pFile == NULL){
        printf("Error: cannot open file!\n");
        return;
    }

    Credentials c; // creat variable of structure

    printf("Enter website (domain): ");
    fgets(c.domain, MAX_STRING_SIZE_SMALL, stdin);
    c.domain[strcspn(c.domain, "\n")] = 0; // delete newline


    printf("Enter login: ");
    fgets(c.login, MAX_STRING_SIZE_LARGE, stdin);
    c.login[strcspn(c.login, "\n")] = 0;


    printf("Enter password: ");
    fgets(c.password, MAX_STRING_SIZE_LARGE, stdin);
    c.password[strcspn(c.password, "\n")] = 0;

    encryptDecrypt(c.password); // encrypting password

    fprintf(pFile, "%s,%s,%s\n", c.domain, c.login, c.password );
    fclose(pFile);

    printf("Credential added successfully!\n");
}

void deleteCredentials() {

    FILE *pFile = fopen("credentials.txt", "r");

    if(pFile == NULL){
        printf("Error: cannot open file!\n");
        return;
    }

    bool found = false;
    char line[175];

    //char name[MAX_STRING_SIZE_SMALL];
    char login[MAX_STRING_SIZE_LARGE];
    char password[MAX_STRING_SIZE_LARGE];

    char name[MAX_STRING_SIZE_SMALL];

    printf("Which website credentials do you want to delete (website name)? ");
    //scanf(" %24[^\n]", name);

    if( scanf(" %24[^\n]", name) != 1) {
        fclose(pFile);
        return;
    }

    FILE *pTempFile = fopen("temp.txt", "w");

    if(pTempFile == NULL){
        printf("Error: cannot open file!\n");
        endProgram(1);
    }

    while(fgets(line, sizeof(line), pFile)){ 
        line[strcspn(line, "\n")] = 0;

        char *websiteName = strtok(line, ","); 
        char *websiteLogin = strtok(NULL, ",");
        char *websitePassword = strtok(NULL, ",");

        if (websiteName == NULL || websiteLogin == NULL || websitePassword == NULL) {
            continue;  // 
        }

         if(strcmp(websiteName, name) == 0) { 
            found = true;
            continue;
        }
        fprintf(pTempFile, "%s,%s,%s\n", websiteName, websiteLogin, websitePassword);
    }

    fclose(pTempFile);
    fclose(pFile);

    remove("credentials.txt");
    rename("temp.txt", "credentials.txt");

    printf("\n");

    if(found) {
        printf("Credential successfully deleted!\n");
    }
    else
    {
        printf("Website not found.\n");
    }
}

void showCredentials() {

    FILE *pFile = fopen("credentials.txt", "r");

    if(pFile == NULL){
        printf("Error: cannot open file!\n");
        return;
    }

    bool found = false;
    char line[175];

    //char name[MAX_STRING_SIZE_SMALL];
    char login[MAX_STRING_SIZE_LARGE];
    char password[MAX_STRING_SIZE_LARGE];

    char name[MAX_STRING_SIZE_SMALL];

    printf("Which website credentials do you want to see (website name)? ");
    scanf(" %24[^\n]", name);

    if (fgets(name, sizeof(name), stdin) == NULL) {
        fclose(pFile);
        return;
    }

    name[strcspn(name, "\n")] = '\0'; // delete \n that could appear at the end

    while(fgets(line, sizeof(line), pFile)){ 
        line[strcspn(line, "\n")] = 0;

        char *websiteName = strtok(line, ","); 
        char *websiteLogin = strtok(NULL, ",");
        char *websitePassword = strtok(NULL, ",");

        if (websiteName == NULL || websiteLogin == NULL || websitePassword == NULL) {
            continue;
        }

         if(strcmp(websiteName, name) == 0) {
            found = true;

            strncpy(login, websiteLogin, sizeof(login) - 1); // copy 
            login[sizeof(login) - 1] = '\0'; // last sign is \0

            strncpy(password, websitePassword, sizeof(password) - 1);
            password[sizeof(password) - 1] = '\0';

            encryptDecrypt(password);
            break;
        }
    }

    fclose(pFile);

    printf("\n");

    if(found) {
        printf("LOGIN: %s\n", login);
        printf("PASSWORD: %s\n", password);

        memset(password, 0, sizeof(password)); // clear memory of critical data
    }
    else
    {
        printf("Website not found.\n");
    }
}

//additional program functions
void endProgram(int endCode) {
    switch(endCode) {

        case 0:
            printf("Ending program without error.\n");
            break;

        case 1:
            printf("Ending program with error.\n");
            break;

        default:
            printf("Error. Ending program...\n");
            exit(1);
    }
    exit(endCode);
}

void encryptDecrypt(char *str) {
    char key = 0xAA; // XOR key

    for(int i = 0; str[i] != '\0' ; i++) {
        str[i] ^= key; // the same as: str[i] = str[i]^ key;
    }
}


//EOF
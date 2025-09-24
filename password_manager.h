#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#define MAX_STRING_SIZE_SMALL 25
#define MAX_STRING_SIZE_LARGE 50

typedef struct 
{
    char website[MAX_STRING_SIZE_SMALL];
    char login[MAX_STRING_SIZE_LARGE];
    char password[MAX_STRING_SIZE_LARGE];

} Credentials;


// main program functions
void addCredentials();
void deleteCredentials();
void showCredentials();

//additional program functions
void endProgram(int endCode);
void encryptDecrypt(char *str);

#endif
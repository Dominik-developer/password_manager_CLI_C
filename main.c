#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "password_manager.h"

int main() {
 
    int choice = -1;

    while (choice != 0) {
        printf("\n");
        printf("\n==== PASSWORD MANAGER ====\n");
        printf("0 - End program\n");
        printf("1 - Show password\n");
        printf("2 - Add new password\n");
        printf("3 - Delate password\n");
        printf("===========================\n");
        printf("Choose action: ");
        scanf("%d", &choice);

        switch(choice) {
            case 0:
                printf("Ending program...\n");
                printf("\n");
                endProgram(0);
                break;

            case 1:
                printf("\n");
                showCredentials();
                break;

            case 2:
                printf("\n");
                addCredentials();
                break;

            case 3:
                printf("\n");
                deleteCredentials();
                break;

            default:
                printf("Invalid option!\n");
        }
    }
    return 0;
}


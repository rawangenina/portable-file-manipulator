#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "text_ops.h"

int main() {
    int choice;

    while (1) {
        // Display menu options
        printf("=== FileManipulator Menu ===\n");
        printf("1. Append text to file\n");
        printf("2. Insert text in file\n");
        printf("3. Clear file\n");
        printf("4. Show file content\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        // Get user choice and validate input
        if (scanf_s("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n'); // clear invalid input
            continue;
        }
        while (getchar() != '\n'); // remove leftover newline

        // Perform selected operation
        switch (choice) {
        case 1: append_text(); break;
        case 2: insert_text(); break;
        case 3: clear_file(); break;
        case 4: show_file(); break;
        case 5: exit(0); // exit program
        default: printf("Invalid choice.\n"); break;
        }
        printf("\n");
    }

    return 0;
}

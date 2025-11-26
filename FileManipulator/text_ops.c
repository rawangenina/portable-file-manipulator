#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_ops.h"

// Append text at the end of a file
void append_text() {
    char filename[256];
    char text[1024];

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // remove trailing newline

    printf("Enter text to append: ");
    fgets(text, sizeof(text), stdin);

    FILE* file = fopen(filename, "a"); // open file in append mode
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    fprintf(file, "%s", text); // write text to file
    fclose(file);
    printf("Text appended.\n");
}

// Insert text at a specific position (character index)
void insert_text() {
    char filename[256];
    char text[1024];
    int position;

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    printf("Enter text to insert: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter position (character index): ");
    scanf_s("%d", &position);
    while (getchar() != '\n'); // remove leftover newline

    FILE* file = fopen(filename, "r+"); // open for reading and writing
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    // Find file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);

    // If position > filesize, insert at the end
    if (position > filesize) position = filesize;

    // Read the content after the insert position into a buffer
    char* buffer = malloc(filesize - position + 1);
    fseek(file, position, SEEK_SET);
    fread(buffer, 1, filesize - position, file);

    // Insert new text
    fseek(file, position, SEEK_SET);
    fwrite(text, 1, strlen(text), file);
    fwrite(buffer, 1, filesize - position, file);

    free(buffer);
    fclose(file);
    printf("Text inserted.\n");
}

// Clear all content of a file
void clear_file() {
    char filename[256];
    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    FILE* file = fopen(filename, "w"); // opening in "w" mode clears the file
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }
    fclose(file);
    printf("File cleared.\n");
}

// Show file content with paging
void show_file() {
    char filename[256];
    int lines_per_page;

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    printf("Enter number of lines per page: ");
    scanf_s("%d", &lines_per_page);
    while (getchar() != '\n'); // remove leftover newline

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    char line[1024];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        count++;

        // Pause after lines_per_page lines
        if (count == lines_per_page) {
            printf("Press Enter to continue...");
            getchar();
            count = 0;
        }
    }
    fclose(file);
}

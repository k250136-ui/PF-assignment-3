#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 4
#define MAX_INPUT 1024     

void* safeMalloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        perror("Error: Memory allocation failed");
        exit(1);
    }
    return ptr;
}

void* safeRealloc(void *ptr, size_t size) {
    void *temp = realloc(ptr, size);
    if (!temp) {
        perror("Error: Reallocation failed");
        free(ptr);
        exit(1);
    }
    return temp;
}

void insertLine(char ***lines, int *count, int *capacity, int index, const char *text) {

    if (index < 0 || index > *count) {
        printf("Invalid index!\n");
        return;
    }

    if (*count == *capacity) {
        *capacity *= 2;
        *lines = safeRealloc(*lines, (*capacity) * sizeof(char*));
    }

    memmove(&(*lines)[index + 1], &(*lines)[index], (*count - index) * sizeof(char*));

    (*lines)[index] = safeMalloc(strlen(text) + 1);
    strcpy((*lines)[index], text);

    (*count)++;
}

void deleteLine(char ***lines, int *count, int index) {
    if (index < 0 || index >= *count) {
        printf("Invalid index!\n");
        return;
    }

    free((*lines)[index]);  

    memmove(&(*lines)[index], &(*lines)[index + 1], (*count - index - 1) * sizeof(char*));

    (*count)--;
}

void printAllLines(char **lines, int count) {
    printf("\n----- TEXT BUFFER -----\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i, lines[i]);
    }
}

void shrinkToFit(char ***lines, int count) {
    *lines = safeRealloc(*lines, count * sizeof(char*));
    printf("Memory shrunk to fit %d lines.\n", count);
}

void saveToFile(char **lines, int count, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", lines[i]);
    }

    fclose(fp);
    printf("Saved to %s\n", filename);
}

void loadFromFile(char ***lines, int *count, int *capacity, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < *count; i++) free((*lines)[i]);
    *count = 0;

    char buffer[MAX_INPUT];

    while (fgets(buffer, MAX_INPUT, fp)) {
        buffer[strcspn(buffer, "\n")] = '\0'; 

        if (*count == *capacity) {
            *capacity *= 2;
            *lines = safeRealloc(*lines, (*capacity) * sizeof(char*));
        }

        (*lines)[*count] = safeMalloc(strlen(buffer) + 1);
        strcpy((*lines)[*count], buffer);
        (*count)++;
    }

    fclose(fp);
    printf("File loaded successfully.\n");
}

void freeAll(char ***lines, int *count) {
    for (int i = 0; i < *count; i++) {
        free((*lines)[i]);
    }
    free(*lines);
    *lines = NULL;
    *count = 0;
}

int main() {
    char **lines = safeMalloc(INITIAL_CAPACITY * sizeof(char*));
    int count = 0;
    int capacity = INITIAL_CAPACITY;

    int choice, index;
    char input[MAX_INPUT];
    char filename[100];

    while (1) {
        printf("\n------ TEXT EDITOR MENU ------\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Shrink to Fit\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

        case 1:
            printf("Enter index to insert at: ");
            scanf("%d", &index);
            getchar();

            printf("Enter text: ");
            fgets(input, MAX_INPUT, stdin);
            input[strcspn(input, "\n")] = '\0';

            insertLine(&lines, &count, &capacity, index, input);
            break;

        case 2:
            printf("Enter index to delete: ");
            scanf("%d", &index);
            deleteLine(&lines, &count, index);
            break;

        case 3:
            printAllLines(lines, count);
            break;

        case 4:
            shrinkToFit(&lines, count);
            break;

        case 5:
            printf("Enter filename: ");
            scanf("%s", filename);
            saveToFile(lines, count, filename);
            break;

        case 6:
            printf("Enter filename: ");
            scanf("%s", filename);
            loadFromFile(&lines, &count, &capacity, filename);
            break;

        case 7:
            freeAll(&lines, &count);
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "members.txt"
#define MAX_NAME 25
#define MAX_BATCH 5
#define MAX_MEMBERSHIP 10
#define MAX_INTEREST 10

typedef struct {
    int id;
    char name[MAX_NAME];
    char batch[MAX_BATCH];         
    char membership[MAX_MEMBERSHIP]; 
    char regDate[11];              
    char dob[11];                  
    char interest[MAX_INTEREST];    
} Student;

void addStudent() {
    FILE *fp = fopen(FILENAME, "a"); 
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    Student s;

    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    getchar();
    FILE *check = fopen(FILENAME, "r");
    if (check) {
        Student temp;
        while (fscanf(check, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",&temp.id, temp.name, temp.batch, temp.membership, temp.regDate, temp.dob, temp.interest) != EOF) {
            if (temp.id == s.id) {
                printf("Student ID already exists!\n");
                fclose(fp);
                fclose(check);
                return;
            }
        }
        fclose(check);
    }

    printf("Enter Full Name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Batch (CS, SE, Cyber Security, AI): ");
    fgets(s.batch, MAX_BATCH, stdin);
    s.batch[strcspn(s.batch, "\n")] = 0;

    printf("Enter Membership Type (IEEE/ACM): ");
    fgets(s.membership, MAX_MEMBERSHIP, stdin);
    s.membership[strcspn(s.membership, "\n")] = 0;

    printf("Enter Registration Date (YYYY-MM-DD): ");
    fgets(s.regDate, 11, stdin);
    s.regDate[strcspn(s.regDate, "\n")] = 0;

    printf("Enter Date of Birth (YYYY-MM-DD): ");
    fgets(s.dob, 11, stdin);
    s.dob[strcspn(s.dob, "\n")] = 0;

    printf("Enter Interest (IEEE/ACM/Both): ");
    fgets(s.interest, MAX_INTEREST, stdin);
    s.interest[strcspn(s.interest, "\n")] = 0;

    fprintf(fp, "%d|%s|%s|%s|%s|%s|%s\n", s.id, s.name, s.batch, s.membership, s.regDate, s.dob, s.interest);
    fclose(fp);
    printf("Student added successfully!\n");
}

void viewStudents() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    Student s;
    printf("\nAll Registered Students:\n");
    printf("ID | Name | Batch | Membership | RegDate | DOB | Interest\n");
    printf("------------------------------------------------------------\n");
    while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",&s.id, s.name, s.batch, s.membership, s.regDate, s.dob, s.interest) != EOF) {
        printf("%d | %s | %s | %s | %s | %s | %s\n",s.id, s.name, s.batch, s.membership, s.regDate, s.dob, s.interest);
    }
    fclose(fp);
}

void updateStudent() {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    Student s;
    int found = 0;

    while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",&s.id, s.name, s.batch, s.membership, s.regDate, s.dob, s.interest) != EOF) {
        if (s.id == id) {
            found = 1;
            printf("Enter new Batch (CS, SE, Cyber Security, AI): ");
            fgets(s.batch, MAX_BATCH, stdin);
            s.batch[strcspn(s.batch, "\n")] = 0;

            printf("Enter new Membership Type (IEEE/ACM): ");
            fgets(s.membership, MAX_MEMBERSHIP, stdin);
            s.membership[strcspn(s.membership, "\n")] = 0;
        }
        fprintf(temp, "%d|%s|%s|%s|%s|%s|%s\n", s.id, s.name, s.batch, s.membership, s.regDate, s.dob, s.interest);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("Student updated successfully!\n");
    else
        printf("Student ID not found!\n");
}

void deleteStudent() {
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    Student s;
    int found = 0;

    while (fscanf(fp, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",&s.id, s.name, s.batch, s.membership, s.regDate, s.dob, s.interest) != EOF) {
        if (s.id == id) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d|%s|%s|%s|%s|%s|%s\n", s.id, s.name, s.batch, s.membership, s.regDate, s.dob, s.interest);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("Student deleted successfully!\n");
    else
        printf("Student ID not found!\n");
}

void menu() {
    int choice;
    do {
        printf("\nIEEE/ACM Membership Manager\n");
        printf("1. Register New Student\n");
        printf("2. Update Student Info\n");
        printf("3. Delete Student\n");
        printf("4. View All Students\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: viewStudents(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
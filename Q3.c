#include <stdio.h>
#include <string.h>

struct employee
{
    int id;
    char name[30];
    char designation[30];
    double salary;
};

void displayEmployees(struct employee emp[], int n)
{
    printf("ID\tName\t\tDesignation\tSalary\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%-10s\t%-12s\t%.2lf\n", emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
}

void findHighestSalary(struct employee emp[], int n)
{

    double max = emp[0].salary;
    int index = 0;
    for (int i = 1; i < n; i++)
    {
        if (max < emp[i].salary)
        {
            max = emp[i].salary;
            index = i;
        }
    }
    printf("Employee who has the highest salary\n");
    printf(" /t%d\n \t%-10s \n \t%-12s \n \t%.2lf\n", emp[index].id, emp[index].name, emp[index].designation, emp[index].salary);
}

void searchEmployee(struct employee emp[], int n)
{
    int choice;
    printf("\nSearch by:\n1. ID\n2. Name\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        int id;
        printf("Enter Employee ID: ");
        scanf("%d", &id);

        for (int i = 0; i < n; i++)
        {
            if (emp[i].id == id)
            {
                printf("Record Found!\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2lf\n",emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                return;
            }
        }
        printf("No employee found with this ID.\n");
    }
    else if (choice == 2)
    {
        char name[50];
        printf("Enter Employee Name: ");
        scanf("%s", name);

        for (int i = 0; i < n; i++)
        {
            if (strcmp(emp[i].name, name) == 0)
            {
                printf("Record Found!\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2lf\n",emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                return;
            }
        }
        printf("No employee found with this Name.\n");
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

void giveBonus(struct employee emp[], int n, double threshold) {
    for (int i = 0; i < n; i++) {
        if (emp[i].salary < threshold) {
            emp[i].salary = emp[i].salary * 1.10; 
        }
    }
}

int main()
{

    int n;
    printf("Enter number of Employees: ");
    scanf("%d", &n);
    struct employee emp[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter employee %d data\n", i + 1);
        printf("Name: ");
        scanf("%s", emp[i].name);
        printf("ID: ");
        scanf("%d", &emp[i].id);
        printf("Designation: ");
        scanf("%s", emp[i].designation);
        printf("Salary: ");
        scanf("%lf", &emp[i].salary);
    }
printf("-------------------------------------------------------------------------\n");
    displayEmployees(emp, n);
printf("-------------------------------------------------------------------------\n");
    findHighestSalary(emp, n);
printf("-------------------------------------------------------------------------\n");
    searchEmployee(emp, n);
printf("-------------------------------------------------------------------------\n");
    giveBonus(emp, n, 50000);
    printf("-------------------------------------------------------------------------\n");
    printf("After Bonus\n");
    displayEmployees(emp, n);
printf("-------------------------------------------------------------------------\n");
    return 0;
}
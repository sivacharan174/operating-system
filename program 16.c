#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for an employee
struct Employee {
    int empID;
    char name[50];
    float salary;
};

int main() {
    FILE *file;
    struct Employee emp;

    // Open the file in binary mode for read and write
    file = fopen("employeeDetails.dat", "rb+");

    if (file == NULL) {
        // If the file doesn't exist, create and open it
        file = fopen("employeeDetails.dat", "wb+");
        if (file == NULL) {
            printf("Error in creating the file.\n");
            return 1;
        }
    }

    int choice;
    do {
        printf("\nEmployee Details Menu:\n");
        printf("1. Add Employee Details\n");
        printf("2. View All Employee Details\n");
        printf("3. Search for an Employee\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add Employee Details
                fseek(file, 0, SEEK_END); // Move the file pointer to the end
                printf("Enter employee ID: ");
                scanf("%d", &emp.empID);
                printf("Enter employee name: ");
                scanf("%s", emp.name); // Assuming no space in name
                printf("Enter employee salary: ");
                scanf("%f", &emp.salary);
                fwrite(&emp, sizeof(struct Employee), 1, file);
                break;

            case 2:
                // View All Employee Details
                rewind(file); // Move the file pointer to the beginning
                printf("\nEmployee Details:\n");
                while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
                    printf("ID: %d, Name: %s, Salary: %.2f\n", emp.empID, emp.name, emp.salary);
                }
                break;

            case 3:
                // Search for an Employee
                int searchID;
                printf("Enter employee ID to search: ");
                scanf("%d", &searchID);
                rewind(file);
                while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
                    if (emp.empID == searchID) {
                        printf("Employee found - ID: %d, Name: %s, Salary: %.2f\n", emp.empID, emp.name, emp.salary);
                        break;
                    }
                }
                if (feof(file)) {
                    printf("Employee with ID %d not found.\n", searchID);
                }
                break;

            case 4:
                // Exit
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    fclose(file); // Close the file before exiting

    return 0;
}

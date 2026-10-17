#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utils.h"

#define MAX_EMP 100
#define NAME_LEN 50 
#define DEPT_LEN 30

int empID[MAX_EMP];
char empName[MAX_EMP][NAME_LEN];
char empDept[MAX_EMP][DEPT_LEN];
double empBasic[MAX_EMP];
double empHousing[MAX_EMP];
double empTransport[MAX_EMP];
double empOther[MAX_EMP];
int empCount = 0;

int findEmployeeByID(int id)
{
    int i;
    for(i = 0; i <empCount; i++) {
        if (empID[i] == id) {
            return i;
        }
    } return -1;
}

int getEmployeeCount(void)
{
    return empCount;
}

double getEmployeeGross(int index)
{
    if (index < 0 || index > empCount) {
        return 0;
    }
    return empBasic[index] + empHousing[index] + empTransport[index] + empOther[index];
}

double calculateTax(double gross)
{ 
    double rate;

    if (gross <= 5000) {
        rate = 0.0;
    } else if (gross <= 10000) {
        rate = 0.10;
    } else if (gross <= 20000) {
        rate = 0.20;
    } else {
        rate = 0.30;
    } 
    return gross * rate;
} 

void printfEmployeeRow(int i)
{ 
    printf("%-6d %-20s %-15s N$%10.2f\n",
        empID[i], empName[i], empDept[i], getEmployeeGross(i));
    }
    

    void addEmployee(void)
    {
        int id;

        if (empCount >= MAX_EMP) {
            printf("Employee list is full.\n");
            return;
        }

        id = readInt("Employee ID (1-999999): ", 1, 999999);
        if (findEmployeeByID(id) != -1) {
            printf("An employee with that ID already exists.\n");
            return;
        }
        
        empID[empCount] = id;
        readString("Name: ", empName[empCount], NAME_LEN);
        readString("Department: ", empDept[empCount], DEPT_LEN);
        empBasic[empCount]   =  readDouble("Basic salary (N$): ", 0);
        empHousing[empCount] =  readDouble("Housing allowance (N$): ", 0);
        empTransport[empCount] = readDouble("Transport allowance (N$): ", 0);
        empOther[empCount]    = readDouble("Other allowance (N$): ", 0);

        empCount++;
        printf("Employee added successfully.\n");
    }

    void displayEmployees(void)
    { 
        int i;

        if (empCount == 0) {
            printf("No employees registered yet.\n");
            return;
        }

        printf("\n%-6s %-20s %-15s %13s\n", "ID", "Name", "Department", "Gross Salary");
        printf("---------------------------------------------------\n");
        for (i = 0; i < empCount; i++) {
            printfEmployeeRow(i);
        } 
    }
    
    void searchEmployee(void)
    { 
        int option, id, i, found = 0;
        char searchName[NAME_LEN];

        printf("\n1. Search by ID\n2. Search by name\n");
        option = readInt("Choice: ", 1, 2);

        if (option == 1) {
            id = readInt("Enter employee ID: ", 1, 999999);
            i = findEmployeeByID(id);
            if (i != -1) {
                printfEmployeeRow(i);
                found = 1;
            }
        } else {
            readString("Enter employee name: ", searchName, NAME_LEN);
            for (i = 0; i < empCount; i++) {
                if (strcmp(empName[i], searchName) == 0) {
                    printfEmployeeRow(i);
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("Employee not found.\n");
        }
    }
    void calculateSalary(void)
    { 
        int id, i;
        double gross, tax;

        id = readInt("Enter employee ID: ", 1, 999999);
        i = findEmployeeByID(id);
        if (i == -1) {
            printf("Employee not found.\n");
            return;
        }

        gross = getEmployeeGross(i);
        tax = calculateTax(gross);

        printf("Basic salary:        N$%10.2f\n", empBasic[i]);
printf("Housing allowance:   N$%10.2f\n", empHousing[i]);
printf("Transport allowance: N$%10.2f\n", empTransport[i]);
printf("Other allowance:     N$%10.2f\n", empOther[i]);
printf("Gross salary:        N$%10.2f\n", gross);
printf("Tax:                 N$%10.2f\n", tax);
printf("Net salary:          N$%10.2f\n", gross - tax);
    }

    

    void employeeMenu(void)
    {
        int choice;

        do {
            printf("\n-- EMPLOYEE MANAGEMENT ---\n");
            printf("1. Add employee\n");
            printf("2. Display employees\n");
            printf("3. Search for an employee\n");
            printf("4. Calculate salary\n");
            printf("5. Back to main menu\n");
            choice = readInt("Enter your choice: ", 1, 5);

            switch(choice) {
                case 1: addEmployee(); break;
                case 2: displayEmployees(); break;
                case 3: searchEmployee(); break;
                case 4: calculateSalary(); break;
                case 5: break;
            }
        } while (choice != 5);
    }
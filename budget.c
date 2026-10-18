#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utils.h"

#define MAX_DEPT 20
#define DEPT_LEN 30

char budDept[MAX_DEPT][DEPT_LEN];
double budAllocated[MAX_DEPT];
double budSpent[MAX_DEPT];
int budCount = 0;

int findDepartment(const char name[])
{
    int i;
    for (i = 0; i < budCount; i++) {
        if (strcmp(budDept[i], name) == 0) {
            return i;
        }
    } 
    return -1;
}

double calculateRemaining(double allocated, double spent)
{
    return allocated - spent;
}

int getBudgetCount(void)
{ 
    return budCount;
}

double getTotalAllocated(void)
{
    int i;
    double total = 0;
    for (i = 0; i < budCount; i++) {
        total += budAllocated[i];
    }
    return total;
}

double getTotalSpent(void)
{
    int i;
    double total = 0;
    for (i = 0; i < budCount; i++) {
        total += budSpent[i];
    } return total;
}
    

void addDepartmentBudget(void)
{
    char name[DEPT_LEN];

    if (budCount >= MAX_DEPT) {
        printf("Department list is full.\n");
        return;
    }

    readString("Department name: ", name, DEPT_LEN);
    if (findDepartment(name) != -1) {
        printf("That department already has a budget.\n");
        return;
    }

    strcpy(budDept[budCount], name);
    budAllocated[budCount] = readDouble("Allocated budget (N$): ", 0);
    budSpent[budCount] = 0;
    budCount++;
    printf("Department budget added.\n");
}

void recordExpenditure(void)
{ 
    char name[DEPT_LEN];
    int i;
    double amount, remaining;

    if (budCount == 0) {
        printf("No departments yet. Add a department  budget first.\n");
        return;
    }

    readString("Department name: ", name, DEPT_LEN);
    i = findDepartment(name);
    if (i == -1) {
        printf("Department not found.\n");
        return;
    }


    amount = readDouble("Expenditure amount (N$): ", 0);
    budSpent[i] += amount;

    remaining = calculateRemaining(budAllocated[i], budSpent[i]);
    printf("Expenditure recorded. Remaining budget: N$%.2f\n", remaining);
    if (remaining < 0) {
        printf("WARNING: %s has exceeded its budget!\n", budDept[i]);
    }
}

void displayBudgets(void)
{ 
    int i;
    double remaining; 

    if (budCount == 0) {
        printf("No budgets registered yet.\n");
        return;
    }

    for (i = 0; i < budCount; i++) {
        remaining = calculateRemaining(budAllocated[i], budSpent[i]);
        printf("\nDepartment: %s\n", budDept[i]);
        printf("Allocated Budget: N$%.2f\n", budAllocated[i]);
        printf("Expenditure: N$%.2f\n", budSpent[i]);
        printf("Remaining Budget: N$%.2f\n", remaining);
        if (remaining >= 0) {
            printf("Status: WITHIN BUDGET\n");
        } else {
            printf("Status: OVER BUDGET\n");
        }
    }
}


void displayOverBudget(void)
{ 
    int i, found = 0;
    double over;

    for (i = 0; i < budCount; i++) {
        over = budSpent[i] - budAllocated[i];
        if (over > 0) {
            printf("%-20s over by N$%.2f\n", budDept[i], over);
            found = 1;
        }
    }

    if (!found) {
        printf("No departments have exceeded their budget.\n");
    }
}

void budgetMenu(void)
{
    int choice;

    do {
        printf("\n--- BUDGET MANAGEMENT ---\n");
        printf("1. Add department budget\n");
        printf("2. Record expenditure\n");
        printf("3. Display budget information\n");
        printf("4. Show departments over budget\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1: addDepartmentBudget(); break;
            case 2: recordExpenditure(); break;
            case 3: displayBudgets(); break;
            case 4: displayOverBudget(); break;
            case 5: break;
        }
    } while (choice != 5);

}
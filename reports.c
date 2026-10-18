#include <stdio.h>
#include "reports.h"
#include "utils.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void employeeReport(void)
{
    int i;
    int count = getEmployeeCount();
    double salary, total, highest, lowest;

    printf("\n=========== EMPLOYEE REPORT ===========\n");

    if (count == 0) {
        printf("No employees registered yet.\n");
        return;
    }

    highest = getEmployeeGross(0);
    lowest = getEmployeeGross(0);
    total = 0;

    for (i = 0; i < count; i++) {
        salary = getEmployeeGross(i);
        total += salary;
        if (salary > highest) {
            highest = salary;
        }
        if (salary < lowest) {
            lowest = salary;
        }
    }

    printf("Total Employees: %d\n", count);
    printf("Average Salary:  N$%.2f\n", total / count);
    printf("Highest Salary:  N$%.2f\n", highest);
    printf("Lowest Salary:   N$%.2f\n", lowest);
}


void budgetReport(void)
{
    double allocated = getTotalAllocated();
    double spent = getTotalSpent();

    printf("\n============ BUDGET REPORT ============\n");

    if (getBudgetCount() == 0) {
        printf("No budgets registered yet.\n");
        return;
    }

    printf("Total Allocated Budget: N$%.2f\n", allocated);
    printf("Total Expenditure:      N$%.2f\n", spent);
    printf("Remaining Budget:       N$%.2f\n", allocated - spent);

    printf("\nDepartments exceeding budget:\n");
    displayOverBudget();
}


void supplierReport(void)
{
    printf("\n=========== SUPPLIER REPORT ===========\n");
    printf("Total Suppliers: %d\n", getSupplierCount());
    displaySuppliers();
}

void assetReport(void)
{
    printf("\n============ ASSET REPORT =============\n");
    displayAssets();
}


void reportsMenu(void)
{
    int choice;

    do {
        printf("\n--- REPORTS ---\n");
        printf("1. Employee report\n");
        printf("2. Budget report\n");
        printf("3. Supplier report\n");
        printf("4. Asset report\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1: employeeReport(); break;
            case 2: budgetReport(); break;
            case 3: supplierReport(); break;
            case 4: assetReport(); break;
            case 5: break;
        }
    } while (choice != 5);
} 
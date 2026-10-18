#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utils.h"

#define MAX_SUP 50
#define NAME_LEN 50
#define EMAIL_LEN 50
#define PHONE_LEN 20
#define TOWN_LEN 30

int supID[MAX_SUP];
char supName[MAX_SUP][NAME_LEN];
char supEmail[MAX_SUP][EMAIL_LEN];
char supPhone[MAX_SUP][PHONE_LEN];
char supTown[MAX_SUP][TOWN_LEN];
int supCount = 0;


int findSupplierByID(int id)
{
    int i;
    for (i = 0; i < supCount; i++) {
        if (supID[i] == id) {
            return i;
        }
    }
    return -1;
}

int getSupplierCount(void)
{
    return supCount;
}


int isValidEmail(const char email[])
{
    int i;
    int len = strlen(email);
    int at = -1;
    int dot = -1;

    for (i = 0; i < len; i++) {
        if (email[i] == ' ') {
            return 0;
        }
        if (email[i] == '@') {
            if (at != -1) {
                return 0;
            }
            at = i;
        } else if (email[i] == '.' && at != -1) {
            dot = i;
        }
    }

    if (at < 1) {
        return 0;
    }
    if (dot < at + 2) {
        return 0;
    }
    if (dot >= len - 1) {
        return 0;
    }
    return 1;
}

    
int isValidPhone(const char phone[])
{
    int i;
    int len = strlen(phone);

    if (len < 7 || len > 15) {
        return 0;
    }
    for (i = 0; i < len; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return 0;
        }
    }
    return 1;
}

void printSupplierRow(int i)
{
    printf("%-6d %-20s %-26s %-12s %-12s\n",
           supID[i], supName[i], supEmail[i], supPhone[i], supTown[i]);
}


void addSupplier(void)
{
    int id;

    if (supCount >= MAX_SUP) {
        printf("Supplier list is full.\n");
        return;
    }

    id = readInt("Supplier ID (1-999999): ", 1, 999999);
    if (findSupplierByID(id) != -1) {
        printf("A supplier with that ID already exists.\n");
        return;
    }

    supID[supCount] = id;
    readString("Supplier name: ", supName[supCount], NAME_LEN);

    do {
        readString("Email: ", supEmail[supCount], EMAIL_LEN);
        if (!isValidEmail(supEmail[supCount])) {
            printf("Invalid email. Example: name@company.com\n");
        }
    } while (!isValidEmail(supEmail[supCount]));

    do {
        readString("Telephone (digits only): ", supPhone[supCount], PHONE_LEN);
        if (!isValidPhone(supPhone[supCount])) {
            printf("Invalid phone. Use 7 to 15 digits, no spaces or symbols.\n");
        }
    } while (!isValidPhone(supPhone[supCount]));

    readString("Town/Location: ", supTown[supCount], TOWN_LEN);

    supCount++;
    printf("Supplier added successfully.\n");
}

void displaySuppliers(void)
{
    int i;

    if (supCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-26s %-12s %-12s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printf("--------------------------------------------------------------------------------\n");
    for (i = 0; i < supCount; i++) {
        printSupplierRow(i);
    }
}



void searchSupplier(void)
{
    int option, id, i, found = 0;
    char text[NAME_LEN];

    printf("\n1. Search by ID\n2. Search by name\n3. Search by town\n");
    option = readInt("Choice: ", 1, 3);

    if (option == 1) {
        id = readInt("Enter supplier ID: ", 1, 999999);
        i = findSupplierByID(id);
        if (i != -1) {
            printSupplierRow(i);
            found = 1;
        }
    } else if (option == 2) {
        readString("Enter supplier name: ", text, NAME_LEN);
        for (i = 0; i < supCount; i++) {
            if (strcmp(supName[i], text) == 0) {
                printSupplierRow(i);
                found = 1;
            }
        }
    } else {
        readString("Enter town: ", text, NAME_LEN);
        for (i = 0; i < supCount; i++) {
            if (strcmp(supTown[i], text) == 0) {
                printSupplierRow(i);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No matching supplier found.\n");
    }
}

void compareSuppliers(void)
{
    int id1, id2, a, b;

    if (supCount < 2) {
        printf("You need at least two suppliers to compare.\n");
        return;
    }

    id1 = readInt("First supplier ID: ", 1, 999999);
    id2 = readInt("Second supplier ID: ", 1, 999999);

    if (id1 == id2) {
        printf("Please choose two different suppliers.\n");
        return;
    }

    a = findSupplierByID(id1);
    b = findSupplierByID(id2);
    if (a == -1 || b == -1) {
        printf("One or both suppliers were not found.\n");
        return;
    }

    printf("\n");
    printSupplierRow(a);
    printSupplierRow(b);

    if (strcmp(supTown[a], supTown[b]) == 0) {
        printf("\nBoth suppliers are in %s.\n", supTown[a]);
    } else {
        printf("\nThe suppliers are in different towns (%s and %s).\n",
               supTown[a], supTown[b]);
    }

    if (strcmp(supName[a], supName[b]) < 0) {
        printf("Alphabetically, %s comes before %s.\n", supName[a], supName[b]);
    } else if (strcmp(supName[a], supName[b]) > 0) {
        printf("Alphabetically, %s comes before %s.\n", supName[b], supName[a]);
    } else {
        printf("The suppliers have the same name.\n");
    }
}


void supplierMenu(void)
{
    int choice;

    do {
        printf("\n--- SUPPLIER MANAGEMENT ---\n");
        printf("1. Add supplier\n");
        printf("2. Display suppliers\n");
        printf("3. Search for a supplier\n");
        printf("4. Compare two suppliers\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1: addSupplier(); break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier(); break;
            case 4: compareSuppliers(); break;
            case 5: break;
        }
    } while (choice != 5);
}

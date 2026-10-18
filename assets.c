#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "utils.h"

#define MAX_ASSET 100
#define NAME_LEN  50
#define TYPE_LEN  20
#define DEPT_LEN  30
#define COND_LEN  15

int assID[MAX_ASSET];
char assName[MAX_ASSET][NAME_LEN];
char assType[MAX_ASSET][TYPE_LEN];
double assValue[MAX_ASSET];
char assDept[MAX_ASSET][DEPT_LEN];
char assCondition[MAX_ASSET][COND_LEN];
int assCount = 0;


int findAssetByID(int id)
{
    int i;
    for (i = 0; i < assCount; i++) {
        if (assID[i] == id) {
            return i;
        }
    }
    return -1;
}

int getAssetCount(void)
{
    return assCount;
}

double getTotalAssetValue(void)
{
    int i;
    double total = 0;
    for (i = 0; i < assCount; i++) {
        total += assValue[i];
    }
    return total;
}

void selectAssetType(char dest[])
{
    int choice;

    printf("\nAsset type:\n");
    printf("1. Vehicle\n2. Computer\n3. Building\n4. Equipment\n5. Furniture\n");
    choice = readInt("Choose type: ", 1, 5);

    switch (choice) {
        case 1: strcpy(dest, "Vehicle"); break;
        case 2: strcpy(dest, "Computer"); break;
        case 3: strcpy(dest, "Building"); break;
        case 4: strcpy(dest, "Equipment"); break;
        case 5: strcpy(dest, "Furniture"); break;
    }
}


void selectCondition(char dest[])
{
    int choice;

    printf("\nCondition:\n");
    printf("1. Excellent\n2. Good\n3. Fair\n4. Poor\n");
    choice = readInt("Choose condition: ", 1, 4);

    switch (choice) {
        case 1: strcpy(dest, "Excellent"); break;
        case 2: strcpy(dest, "Good"); break;
        case 3: strcpy(dest, "Fair"); break;
        case 4: strcpy(dest, "Poor"); break;
    }
}

void printAssetRow(int i)
{
    printf("%-6d %-20s %-12s N$%11.2f %-15s %-10s\n",
           assID[i], assName[i], assType[i], assValue[i],
           assDept[i], assCondition[i]);
}


void addAsset(void)
{
    int id;

    if (assCount >= MAX_ASSET) {
        printf("Asset register is full.\n");
        return;
    }

    id = readInt("Asset ID (1-999999): ", 1, 999999);
    if (findAssetByID(id) != -1) {
        printf("An asset with that ID already exists.\n");
        return;
    }

    assID[assCount] = id;
    readString("Asset name: ", assName[assCount], NAME_LEN);
    selectAssetType(assType[assCount]);
    assValue[assCount] = readDouble("Purchase value (N$): ", 0);
    readString("Department: ", assDept[assCount], DEPT_LEN);
    selectCondition(assCondition[assCount]);

    assCount++;
    printf("Asset added successfully.\n");
}

void displayAssets(void)
{
    int i;

    if (assCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-12s %13s %-15s %-10s\n",
           "ID", "Name", "Type", "Value", "Department", "Condition");
    printf("--------------------------------------------------------------------------------\n");
    for (i = 0; i < assCount; i++) {
        printAssetRow(i);
    }
    printf("\nTotal assets: %d   Total value: N$%.2f\n", assCount, getTotalAssetValue());
}

void searchAsset(void)
{
    int option, id, i, found = 0;
    char text[NAME_LEN];
    char type[TYPE_LEN];

    printf("\n1. Search by ID\n2. Search by name\n3. Search by type\n4. Search by department\n");
    option = readInt("Choice: ", 1, 4);

    if (option == 1) {
        id = readInt("Enter asset ID: ", 1, 999999);
        i = findAssetByID(id);
        if (i != -1) {
            printAssetRow(i);
            found = 1;
        }
    } else if (option == 2) {
        readString("Enter asset name: ", text, NAME_LEN);
        for (i = 0; i < assCount; i++) {
            if (strcmp(assName[i], text) == 0) {
                printAssetRow(i);
                found = 1;
            }
        }
    } else if (option == 3) {
        selectAssetType(type);
        for (i = 0; i < assCount; i++) {
            if (strcmp(assType[i], type) == 0) {
                printAssetRow(i);
                found = 1;
            }
        }
    } else {
        readString("Enter department: ", text, NAME_LEN);
        for (i = 0; i < assCount; i++) {
            if (strcmp(assDept[i], text) == 0) {
                printAssetRow(i);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No matching asset found.\n");
    }
}


void assetMenu(void)
{
    int choice;

    do {
        printf("\n--- ASSET MANAGEMENT ---\n");
        printf("1. Add asset\n");
        printf("2. Display assets\n");
        printf("3. Search for an asset\n");
        printf("4. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            case 4: break;
        }
    } while (choice != 4);
}
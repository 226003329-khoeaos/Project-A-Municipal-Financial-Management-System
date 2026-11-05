# Project-A--MFMS-

**Course:** PAP521S, Programming in Practice
**Project:** Project A, Foundation System
**Institution:** Namibia University of Science and Technology (NUST)

## Group Members

| Student Number | Name and Surname |
|---|---|
| 226106144 | Hitjevi Ngeama |
| 226141152 | Andreas Werner |
| 226142094 | Ndapewa Kanguloshi |
| 226019497 | Innocentia Ikera |
| 225059096 | Garrison Jr Shilongo |
| 226003329 | Rhiolin Khoeaos |

## Project Description

The MFMS is a menu-driven console application written in ANSI C (C99) for managing
the basic financial operations of a municipality. It covers employees, departmental
budgets, suppliers and municipal assets, and can generate summary reports.
This is the foundation version, which will be extended in Project B.

## System Features

- **Main menu:** clear navigation between all modules, with invalid choices handled.
- **Employee Management:** add, display and search employees, and calculate salary information.
- **Budget Management:** enter budgets and expenditure, calculate the remaining budget,
  show WITHIN BUDGET or EXCEEDED status, and identify departments over budget.
- **Supplier Management:** add, display and search suppliers.
- **Asset Management:** add, display and search the asset register.
- **Reports:** employee, budget, supplier and asset reports.
- **Input validation:** rejects negative values, empty names and invalid numbers.

## Project Structure

```
Project-A-Municipal-Financial-Management-System/
├── main.c
├── utils.c / utils.h
├── employees.c / employees.h
├── budget.c / budget.h
├── suppliers.c / suppliers.h
├── assets.c / assets.h
├── reports.c / reports.h
└── README.md
```

## Compilation Instructions

Requirements: GCC (C99).

Open a terminal in the project folder and run:

```bash
gcc -std=c99 -Wall main.c utils.c employees.c budget.c suppliers.c assets.c reports.c -o mfms
```

## How to Run

Windows:
```bash
mfms.exe
```
Linux/macOS:
```bash
./mfms
```

Then choose an option from the main menu by entering its number.

## Individual Responsibilities

| Member | Responsibility |
|---|---|
| Hitjevi Ngeama | Assest management |
| Andreas Werner | Budget Management |
| Ndapewa Kanguloshi | Supplier Management |
| Innocentia Ikera | Employee Management |
| Garrison Jr Shilongo | Reports |
| Rhiolin Khoeaos | Testing, documentation and Git coordination and also the functions,integration and validation |
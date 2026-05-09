# Bank Management System

A professional C++ Console Application designed to streamline bank account management. This system provides bank administrators with a robust set of tools to manage client records, ensuring data integrity and ease of operation through a clean command-line interface.

## 🚀 Key Features

The system is built around a centralized management dashboard that offers the following functionalities:

1.  **Comprehensive Client Directory**: Displays a complete list of all registered clients in a well-organized tabular format, including account numbers, names, phone numbers, and current balances.
2.  **Secure Client Onboarding**: Allows the addition of new clients with built-in validation logic to ensure each account number is unique, preventing data duplication.
3.  **Efficient Data Removal**: Provides the ability to delete client records by searching for their account number. The system includes a confirmation step to prevent accidental deletions.
4.  **Client Information Updates**: Enables administrators to modify existing client details such as PIN codes, names, and contact information while keeping the account history intact.
5.  **Advanced Search Utility**: Features a dedicated 'Find Client' tool that quickly retrieves and displays all information associated with a specific account number.
6.  **Safe Termination**: A clean exit option that ensures all processes are closed correctly.

## 🛠️ Operational Workflow

To ensure a smooth user experience, the program follows a logical operational flow:

* **Navigation**: The user interacts with the system using a numerical menu (1-6). Each choice leads to a dedicated screen for that specific task.
* **Data Integrity**: Before critical operations like deleting or updating, the system automatically fetches the current record and displays it to the user for verification.
* **Validation Loops**: The program is designed to handle user errors gracefully. For instance, if you try to add a client with an existing ID, the system will prompt you for a new one without crashing.
* **Persistent Storage**: While the interface is console-based, the system is designed to interact with backend data files to ensure that all client information is saved and retrieved accurately every time the program runs.

## 💻 Technical Overview

* **Programming Language**: C++
* **Interface Type**: Command Line Interface (CLI)
* **Development Focus**: The project focuses on core programming concepts including file handling, structural data organization, input validation, and user interface design within a terminal environment.

---
*Developed as part of a programming portfolio to demonstrate proficiency in C++ and system logic.*

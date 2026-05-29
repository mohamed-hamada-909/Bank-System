# Bank Management System (Enhanced Version)

A professional C++ Console Application designed to streamline bank account management. This system provides bank administrators with a robust set of tools to manage client records and perform financial operations, ensuring data integrity through a clean command-line interface.

## 🚀 Key Features

The system is built around a centralized management dashboard that offers the following 6 core functionalities:

1.  **Show Client List**: Displays a complete list of all registered clients in a well-organized tabular format, including account numbers, names, and balances.
2.  **Add New Client**: Allows the addition of new clients with built-in validation logic to ensure each account number is unique.
3.  **Delete Client**: Provides the ability to remove client records securely after a final verification step.
4.  **Update Client Info**: Enables administrators to modify existing client details like PIN codes, names, and phone numbers.
5.  **Find Client**: Quickly retrieves and displays all information associated with a specific account number.
6.  **Program Exit**: Safely terminates the application with a closing message.

## 💰 Transactions Extension (New Update!)

The system now includes a specialized **Transactions Menue Screen** to handle financial activities seamlessly:

*   **Deposit**: Easily add funds to a specific client's account after confirming the account details.
*   **Withdraw**: Securely deduct funds from an account with a smart validation check that prevents withdrawing more than the available balance.
*   **Total Balances**: Generates a summary report showing the balance of each client and calculates the **Total Bank Balances** across all accounts.
*   **Main Menu Integration**: A smooth navigation link that allows you to jump back to the primary management screen.

## 🛠️ Operational Workflow

* **Navigation**: The user interacts with the system using numerical menus (1-6 for main, 1-4 for transactions).
* **Data Integrity**: Critical operations (like withdrawals or updates) require a `y/n` confirmation.
* **Smart Validation**: The program handles edge cases, such as searching for a non-existent account or exceeding the balance limit.
* **Persistent Storage**: All changes are saved to the backend data files to ensure data is preserved.

## 💻 Technical Overview

* **Programming Language**: C++
* **Interface Type**: Command Line Interface (CLI)
* **Logic Focus**: File handling, input validation, and transactional financial logic.

---
*Developed as part of a programming portfolio to demonstrate proficiency in C++ and system logic.*

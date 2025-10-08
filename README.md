## Virtual ATM Simulation

The Virtual ATM Simulation project is a C-based console application that emulates the basic functionalities of an Automated Teller Machine (ATM).

It allows users to interact with a virtual banking system, performing tasks such as checking balances, depositing and withdrawing funds, and reviewing transaction history—all without the need for a physical ATM.

# This project is ideal for learning:

File handling in C (accounts.txt, transactions.txt)

Modular programming using .c and .h files

User authentication logic

Basic data structures for transaction records

## Features

# User Authentication

# Each user account is secured by a PIN.

Only authenticated users can access their account.

# Balance Inquiry

Users can view their current account balance anytime.

# Withdrawals

Withdraw money from the account.

Includes validation to prevent overdrawing.

# Deposits

Add funds to the account.

# Transaction History

Keep a log of deposits and withdrawals in transactions.txt.

# Account Management (Optional Extension)

Admin can add new accounts or remove accounts (can be added as a future improvement).

# File Structure
# File	Description
# atm.c	Implements the ATM operations and logic.
# atm.h	Header file with function declarations.
# main.c	Entry point of the program, manages user input and menu.
# accounts.txt	Stores account numbers, PINs, and balances.
# transactions.txt	Logs user transactions with timestamps.

# Screenshots / Example Usage

(Optional: Add screenshots or terminal examples here)

Welcome to Virtual ATM!
1. Check Balance
2. Deposit
3. Withdraw
4. Transaction History
5. Exit
Enter your choice: _

# Compilation and Execution

# Clone the repository:

git clone https://github.com/manirul13/Virtual_ATM_Simulation.git


Navigate to the project directory:

# cd Virtual_ATM_Simulation


# Compile the code using gcc:

gcc main.c atm.c -o atm


# Run the simulation:

./atm

# How It Works
1. Login: The user enters their account number and PIN.
2. Menu Display: After authentication, a menu allows access to different operations.
3. Transactions: Each transaction is recorded in transactions.txt for future reference.
4. Validation: The program checks for invalid inputs, insufficient funds, and incorrect PINs.


## Future Improvements
1. Add GUI support (e.g., with GTK or Qt).
2. Encrypt accounts.txt and transactions.txt for security.
3. Support multiple currencies.
4. Implement admin features (create, delete accounts).
5. Add unit tests for transaction functions.


## Contributing
1. Contributions are welcome! Please follow these steps:
2. Fork the repository
3. Create a new branch (git checkout -b feature-name).
4. Make your changes.
5. Commit changes (git commit -m "Add feature").
6. Push to branch (git push origin feature-name).
7. Open a pull request.

# Author / Contact

Author: Manirul

GitHub: https://github.com/manirul13

 

# 🏧 Virtual ATM Simulation

A console-based **Virtual ATM Simulation** developed in **C Programming** that mimics the basic functionalities of a real-world ATM. The project uses **file handling** to store account information and transaction history, providing a persistent banking experience.

---

## 📌 Project Overview

The Virtual ATM Simulation allows users to authenticate using their **Account Number** and **PIN**, then perform common banking operations such as checking balance, depositing money, withdrawing cash, changing the PIN, and viewing transaction history.

The project is designed to strengthen concepts of:

- C Programming
- Structures
- File Handling
- Modular Programming
- Authentication
- Input Validation
- Data Persistence

---

## ✨ Features

- 🔐 Secure Login using Account Number and PIN
- 💰 Check Account Balance
- 💵 Deposit Money
- 💸 Withdraw Money
- 🔑 Change ATM PIN
- ⚡ Quick Cash (₹2000)
- 📜 Mini Statement (Last 5 Transactions)
- 💾 Automatic Data Persistence using Files
- 🔒 Masked PIN Input
- ❌ Input Validation
- 📂 Modular Code Structure

---

## 📁 Project Structure

```
Virtual_ATM_Simulation/
│
├── main.c
├── atm.c
├── atm.h
├── accounts.txt
├── transactions.txt
├── Makefile
├── README.md
```

---

## ⚙️ Technologies Used

- Language : C
- Compiler : GCC
- Operating System : Linux
- File Handling
- Standard C Library
- POSIX Terminal APIs (`termios`)

---

## 📚 Concepts Used

- Structures
- Functions
- Arrays
- File Handling
- Modular Programming
- Input Validation
- Pointer
- Authentication
- Data Persistence
- Error Handling

---

## 🏦 ATM Functionalities

### Login

- Account Number Authentication
- 4-Digit PIN Verification
- Maximum Login Attempts
- Masked PIN Entry

---

### Banking Operations

- Check Balance
- Deposit Amount
- Withdraw Amount
- Change PIN
- Fast Cash
- Mini Statement

---

## 💾 Data Storage

### Account Database

```
Name  Account_Number  PIN  Balance
```

Example

```
Manirul_I 8250623436 8250 15000.00
```

---

### Transaction History

Each successful transaction is recorded in:

```
transactions.txt
```

Example

```
8250623436 Deposit 5000
8250623436 Withdraw 1000
8250623436 FastCash 2000
```

---

## ▶️ How to Compile

```bash
gcc main.c atm.c -o atm
```

---

## ▶️ Run

```bash
./atm
```

---

## 🖥️ Sample Output

```
===============================
🏧 WELCOME TO VIRTUAL ATM
===============================

Enter Account Number :
8250623436

Enter PIN :
****

Login Successful

1. Check Balance
2. Deposit Money
3. Withdraw Money
4. Change PIN
5. Fast Cash
6. Mini Statement
7. Exit
```

---

## 🔒 Input Validations

- Invalid Account Number
- Incorrect PIN
- Deposit amount must be positive
- Withdrawal amount must be within limits
- Amount must be a multiple of ₹100
- Insufficient Balance
- Invalid Menu Selection

---

## 🚀 Future Enhancements

- Password Encryption
- PIN Hashing
- Date & Time for Transactions
- Money Transfer
- Account Creation
- Account Deletion
- Admin Panel
- Interest Calculation
- Loan Management
- SMS Notification
- GUI Version
- Database Integration (SQLite/MySQL)

---

## 🎯 Learning Outcomes

Through this project, I gained practical experience in:

- Modular Programming
- File Handling
- Authentication Systems
- Data Persistence
- Console-based User Interface
- Secure Input Handling
- Banking Workflow Simulation

---

## 👨‍💻 Author

**Manirul Islam**

GitHub: https://github.com/manirul13

Repository:

https://github.com/manirul13/Virtual_ATM_Simulation

---

## ⭐ If you found this project useful

Please consider giving the repository a **Star ⭐**.
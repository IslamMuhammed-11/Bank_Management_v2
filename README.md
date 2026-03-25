# Bank_Management_v2
🏦 Bank Management System (C++)

A console-based Bank Management System built using C++.
This project extends a basic banking system by adding user management and permissions, simulating a more realistic environment.

📌 Overview

The system allows managing bank clients and system users with different access levels.
Each user logs in with a username and password and can only access features based on their permissions.

🚀 Features
👤 Client Management
Show all clients
Add new client
Delete client
Update client information
Find client by account number
💰 Transactions
Deposit money
Withdraw money
View total balances
🔐 User Management
Login system (username & password)
Add new users
Delete users
Update users
Find users
Assign permissions to each user
🧠 What I focused on
Applying functional programming style (no OOP)
Separating concerns (UI / Logic / Data handling)
Implementing a role-based access system
Using bitwise operations for permissions
Handling file operations using fstream
Saving and loading data from plain text files
Building custom split and serialization functions
🗂️ Data Storage
Clients file:
Clients.txt

Format:

AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
Users file:
users.txt

Format:

Username#//#Password#//#Permissions
🔑 Permissions System

Each user has a permission value stored as an integer.

-1 → Full access
Other values → Combination of permissions using bitwise operations

Examples:

View clients
Add clients
Delete clients
Transactions
Manage users
⚙️ How it works
User logs in using username and password
System loads users and verifies credentials
Based on permissions, access to features is granted or denied
All data is loaded into memory, modified, then saved back to files
Deletions are handled using a flag (markToDelete)
▶️ How to run
Clone the repository
Open the solution using Visual Studio
Make sure Clients.txt and users.txt exist in the same directory
Run the program
📌 Notes
This project is for learning purposes
Data is stored in plain text (no database)
Passwords are stored as plain text (not secure, just for practice)
🔧 Possible Improvements
Encrypt passwords instead of storing them as plain text
Convert the system to OOP design
Add input validation and better error handling
Improve UI/UX
Replace text files with a real database
💡 What I learned
Designing a system with multiple modules (clients + users)
Implementing permission control using bitwise logic
Managing state and persistence without a database
Writing cleaner and more organized functions

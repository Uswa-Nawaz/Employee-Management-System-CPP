# Employee-Management-System-CPP
This is a console-based management and security interface developed during my 1st semester at UET Lahore (Session 2025-2029). It serves as a practical implementation of Programming Fundamentals concepts, moving from basic syntax to a functional business application
This system relies on pure C++ logic to manage data.
# Logic & Implementation
Data Structure (Parallel Arrays): The system manages employee attributes (ID, Name, Department, Salary) using parallel arrays.
Custom File Parsing: I implemented a manual parsing logic using getline and while loops to read comma-separated values (CSV) from the employees.txt and admin.txt files.
Persistence Layer: Uses fstream (ifstream and ofstream) to ensure that every "Add," "Update," or "Delete" operation is physically saved to the disk.
Search Algorithm: Employs a Linear Search to find specific employee records by matching string IDs within the data arrays.
Security Logic: A dedicated authentication module validates administrator credentials before granting access to the system dashboard.
# Features
Administrative Security: Signup and Sign-in functionality for system protection.
Full CRUD Operations: Add new records, view all data in formatted tables, search by ID, update existing details, and delete records.
Enhanced UX: Utilizes windows.h to provide color-coded feedback (Cyan for headers, Green for success, Red for errors) and custom loading delays for a professional feel.
# Project Documentation
A detailed breakdown of the system flowcharts and technical manual can be found in the: EMS Project Report.

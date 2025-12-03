Department Diary – C Project

This project is a console-based Department Diary Management System built in C. It helps store, manage, and update department activities such as meetings, events, and tasks. The program demonstrates core C programming concepts including structures, binary file handling, input validation, temporary file usage, and menu-driven navigation.

Project Overview

The system maintains a diary of departmental activities. Each entry contains:

ID (auto-generated)

Activity Name

Date

Time

Duration

Address

All records are saved in a binary file (department_diary.dat) for permanent storage.

Features
1. Add Activity

Automatically assigns a unique ID using the next_id() function.

Accepts details like name, date, time, duration, and address.

Handles input formatting and newline removal.

Saves the entry into a binary file in append mode.

2. View All Records

Displays all saved activities in a formatted table.

Shows ID, Name, Date, Time, Duration, and Address.

If no file exists, informs the user that no records are available.

3. Edit Activity

Prompts for an ID to edit.

Uses a temporary file to safely rewrite the updated records.

Replaces the old file after updating to avoid data corruption.

4. Delete Activity

Deletes an entry by matching the ID.

Uses a temporary file to filter out the selected record.

Ensures clean and safe deletion without altering binary data directly.

5. Follow-up

Shortcut to view all existing activities again.

Helps in reviewing records after add/edit/delete operations.

6. Exit

Closes the program and ends execution.

Concepts Used
Structures

A structure Diary is used to hold all activity-related information in one record.

Binary File Handling

Includes usage of:

fopen() modes: "rb", "wb", "ab"

fread() and fwrite()

Temporary file operations for safe updates

remove() and rename() for file replacement

Menu-driven Programming

Uses a loop-based interface allowing users to repeatedly interact until they choose to exit.

Input Validation

Checks for invalid scanf() inputs

Clears buffer to avoid unwanted input issues

Removes newline characters using strcspn()

Persistent Storage

All data is stored in department_diary.dat, ensuring it remains available between program runs.

File Structure
Department_Diary/
│
├── main.c                # Main source code
├── department_diary.dat  # Generated binary data file
└── README.md             # Project documentation

How to Run
gcc main.c -o diary
./diary

Learning Outcomes

This project helps users understand:

CRUD operations in C

Efficient use of structures

Working with binary files

Safe editing and deletion techniques

Input handling and buffer management

Real-world implementation of file-based applications

Possible Future Enhancements

Search functionality (by date or keyword)

Sorting entries by date or time

Exporting diary entries to text or CSV

Graphical interface (using C libraries)

Password-protected access

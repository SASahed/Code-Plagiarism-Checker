Code Plagiarism Checker

This project is a C-based Code Plagiarism Detection System with a built-in user authentication module.
It allows users to register, log in, and then use the system to compare two C program files for similarity.

🔐 User Authentication

Users can Register with a username and password.

Credentials are stored in register.txt.

The system verifies login before allowing access.

Prevents unauthorized use of the plagiarism checker.

🔎 Core Features
1. Comment Removal

Removes both:
// (single-line comments),
/* … */ (multi-line comments)

Ensures only meaningful code is compared.

3. Normalization

Converts all characters to lowercase,
removes extra spaces, tabs, and line breaks,
creates a fair comparison between different coding styles

5. File Comparison

Reads two code files,
cleans both files,
compares character-by-character

Calculates:

Comparable length,
matching characters,
similarity percentage

4. Report Generation

Automatically generates report.txt containing:

Comparable characters,
number of matches,
final percentage similarity,
allows easy documentation of results.

6. Interactive Menus

Authentication Menu,
main Menu (Plagiarism Check, View Report, Exit)

📁 Files Created

1. register.txt → stores username & password

2. report.txt → stores plagiarism check result

🧪 How It Works

1. User logs in

2. Selects Plagiarism Check

3. Enters file path of file 1 and file 2

4. Program cleans both files

5. Calculates and displays similarity

6. Saves report automatically

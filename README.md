# SQL-Database-Sim

By Bilash Sarkar

SQL-Database-Sim is a lightweight, file-based SQL database simulator built entirely from scratch in C++ using regular expressions. Designed as a final project for a university database systems course, this tool interprets and executes simplified SQL commands without relying on any external database engine—just pure logic and file I/O.

The goal of this project was to deepen my understanding of how SQL query processing works under the hood. Instead of relying on existing database management systems, I built a minimal one myself, simulating the basic behavior of SQL operations such as CREATE, INSERT, and SELECT, including JOIN and WHERE clauses. This allowed me to explore string parsing, file handling, and control flow in C++, while mastering the use of regex for command interpretation.


Technologies Used
- C++ for all logic, file manipulation, and program structure
- Regex (C++ <regex> library) to parse and validate SQL-like command inputs
- File I/O (using .txt files in a /database folder to simulate table storage)
  

Setup and Installation
1. Clone this repository or download the source files.
2. Ensure a folder named database exists in the same directory as the executable.
3. Compile the program using a C++ compiler, for example: g++ -std=c++23 main.cpp -o sql_sim
4. Run it passing the SQL command as an argument:
   ex.  ./sql_sim "CREATE TABLE students (id, name, major)"
        ./sql_sim "INSERT INTO students VALUES(1, 'Alice', 'CS')"
        ./sql_sim "SELECT * FROM students"


Supported Commands

- Table creation
    CREATE TABLE tablename (col1, col2, col3, ...)
  
- Insert values
    INSERT INTO tablename VALUES(value1, 'value2', , 'value4')
    (Handles numeric and quoted string values; supports empty fields with extra commas.)
  
- Basic selection
    SELECT * FROM tablename
    SELECT col1, col2 FROM tablename
  
- Conditional selection
    SELECT * FROM tablename WHERE col = 'value'
    (Supports string or numeric comparisons, including optional !=, <, >, etc.)
  
- Inner Join
    SELECT * FROM table1 JOIN table2 ON table1.col = table2.col WHERE ...

All SQL keywords and table/column names are case-insensitive. Data values are case-sensitive.

Example Output:
$ ./sql_sim "SELECT name, major FROM students WHERE id = 1"
name,major
Alice,CS

My Contributions & Takeaways
- Implemented a mini SQL interpreter using only file-based storage and C++.
- Learned to use regular expressions effectively for parsing structured input.
- Developed robust logic for joins and filtering without a traditional database engine.
- Overcame challenges like parsing quoted vs numeric values, handling inconsistent spacing, and aligning output formatting.

Roadblocks & Fixes
- Regex complexity: Initially struggled to extract column lists and JOIN syntax cleanly. I refined my regex patterns and string split logic iteratively to improve accuracy.


This project pushed me to think like a database engine and exposed me to the inner workings of query parsing and execution. It strengthened both my C++ fundamentals and my appreciation for how powerful—but deceptively complex—SQL operations really are under the hood.

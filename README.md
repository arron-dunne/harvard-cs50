# Harvard University's CS50: Introduction to Computer Science

Problems and labs from the Harvard University CS50 course.

## C
The first half of the course introduces the C programming language and uses it for exercises. C is a low-level language and using it helps to understand the fundamentals of progamming and essential concepts. 
- **Type Declarations** are needed for all functions and variables and casting between types (integers and floats for example) must be explicit and declared by the programmer. This teaches how different data types are treated differently by the computer. 
- **Memory Mangement** must also be done explicitly by assigning memory using `malloc` and releasing it using `free` to prevent memory leaking.
- **Compiling into Executables** to run each program. This teaches how programs written in human-readable text are converted into binary files which the computer understands.

## Python
In the second half of the course, Python is introduced for the main programming language. Python is a more abstract language compared to C with memory management, compilation and data types handled by the Python interpreator, so the programmer doesn't need to consider these. This simplification (for the programmer, not the interpreator, which in many ways has to be more complex than the C compiler) means that more advanced programs can be written with cleaner, more concise code. 

## SQL
In week 7, SQL is introduced for accessing and storing data in a database. A SQLite database is created and SQL statements are written in files. These SQL files can be executed on the terminal (inside the python virtual environment) using `cat <filename.sql> | sqlite <database.db>`.

## CS50 Library
The programs in this course make use of the [CS50 C Library](https://github.com/cs50/libcs50). For simplicity, the library is included in `lib/` and linked to each C program during compilation.

## Usage
1. Download or clone the repository and navigate to the root folder
2. Run `make` to compile all C programs
3. Or run `make <program>` to build just a single program
4. For python projects, create a virtual environment and install all pip modules in `requirements.txt`
3. Run any of the programs (with correct arguments) test their functionality
4. Run `make clean` (in root directory) to remove all compiled C binaries


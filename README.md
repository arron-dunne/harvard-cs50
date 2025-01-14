# Harvard University's CS50: Introduction to Computer Science

This repository contains completed problems and labs from Harvard University's [CS50 Course](https://cs50.harvard.edu/x/2022/). The course teaches computer science and how to write efficient programs. Topics include abstraction, algorithms, data structures, encapsulation, resource management, security, software engineering, and web development.

Download or clone the repository and navigate to the root folder to get started.

## C
The first 5 weeks of the course introduce the C programming language, and it's used for the exercises. C is a low-level language, and using it provides an understanding of the fundamentals of programming and essential concepts, such as: 
- **Type Declarations -** needed for all functions and variables, casting between types (integers and floats, for example) must be explicit and declared by the programmer. This teaches how different data types are handled and stored by the computer. 
- **Memory Management -** blocks of memory must be explicitly allocated using `malloc`, and released using `free` to prevent memory leaks.
- **Compiling into Executables -** code must be compiled in order to run a program. Programs written in human-readable text are converted into binary files by a compiler which the computer understands.

### Running C Programs
- In the root folder, run `make` to compile all C programs.
- Or run `make <program>` to build just a single program (see the [MakeFile](/Makefile)).
- Run compiled program, with any required arguments (e.g `./problems/week1/hello`)
- To delete all compiled binaries, use `make clean`

### CS50 C Library
The C programs in this course make use of the [CS50 C Library](https://github.com/cs50/libcs50). The library is included in `lib/` and linked to each C program during compilation.

## Python
In the second half of the course, Python is introduced as the main programming language. Python is a more abstract language compared to C, with memory management, compilation, and data types handled by the Python interpreter, freeing some responsibility from the programmer. This abstraction means that more advanced programs can be written with cleaner, more concise code. 

### Running Python Programs
- In the root folder, create a virtual environment `python -m venv .venv`
- Activate the new environment `source .venv/bin/activate`
- Install all required pip modules `pip install -r requirements.txt`
- Run Python programs to test their functionality (e.g. `python problems/week6/credit.py`)
- For Flask apps, navigate to the project folder and execute `flask run`

## SQL
In week 7, we start to use databases as a way of storing and accessing data. The language used to communicate with a database is SQL. We also use the SQLite Python module to handle database management.

### Running SQL Programs
- Make sure the Python virtual environment is active
- Files ending with the `.db` extension are SQLite databases and can be opened with the command `sqlite3 <database.db>`
- On the SQLite terminal, run any SQL commands.
- Files ending with the `.sql` extension contain SQL statements which can be run on a database using `cat <filename.sql> | sqlite <database.db>`.

## Web Development
In week 8, simple websites are made using HTML, CSS, and JavaScript. These websites consist of a front-end only, not a backend. 

### Running Web Pages
- To view these pages, it is recommended to open the projects in VS Code and use the [Preview on Web Server](https://marketplace.visualstudio.com/items?itemName=yuichinukiyama.vscode-preview-server) extension to view them. 
- Alternatively, create a web server backend and serve the `index.html` page, which contains links to the CSS and JavaScript files.

## Final Project
The final project was to develop a software program, showing all the skills learnt throughout this course.
I decided to make a web application for saving user recipes using Flask, showcasing my skills in web development. The app is called Foodie and I saved it in a seperate GitHub
repository.

[Foodie Repository](https://github.com/arron-dunne/foodie)
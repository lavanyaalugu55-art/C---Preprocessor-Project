# C---Preprocessor-Project
Implementation of a C Preprocessor using C programming, featuring comment removal, header file inclusion, and macro handling.

# C Preprocessor Project

## 📌 Project Description

The C Preprocessor is a mini project developed using C programming. It performs preprocessing operations on C source files before compilation. The project implements important preprocessor functionalities such as comment removal, header file inclusion, and macro handling.

The preprocessor reads a C source file, processes the preprocessing directives, and generates a preprocessed output file named `input.i`.

## 🎯 Objectives

- To understand the working of the C preprocessor.
- To remove single-line and multi-line comments.
- To include standard and user-defined header files.
- To handle object-like macros.
- To handle function-like macros.
- To generate a preprocessed output file.

## ⚙️ Features

1. **Comment Removal**
   - Removes single-line comments (`//`).
   - Removes multi-line comments (`/* */`).

2. **File Inclusion**
   - Supports standard header files such as `stdio.h`.
   - Supports user-defined header files.
   - Copies header contents into the output file.

3. **Macro Handling**
   - Identifies object-like macros.
   - Identifies function-like macros.
   - Stores macro names for processing.

4. **Output Generation**
   - Generates the preprocessed file `input.i`.

## 🛠️ Technologies Used

- Programming Language: C
- Compiler: GCC
- Operating System: Linux
- Build Tool: Makefile
- Editor: VS Code / Vim

## 📂 Project Structure

```text
C-Preprocessor-Project/
│
├── main.c
├── comment_removal.c
├── file_inclusion.c
├── macro_handler.c
├── preprocessor.h
├── Makefile
├── input.c
├── myheader.h
└── input.i
```

## 🚀 How to Compile and Run

### Step 1: Clone the Repository

```bash
git clone YOUR_GITHUB_REPOSITORY_URL
```

### Step 2: Navigate to the Project Directory

```bash
cd C-Preprocessor-Project
```

### Step 3: Compile the Project

```bash
make
```

### Step 4: Run the Project

```bash
./preprocessor input.c
```

### Step 5: View the Output

```bash
cat input.i
```

## 💻 Sample Input

```c
#include <stdio.h>
#include "myheader.h"

#define PI 3.14
#define SQUARE(x) ((x) * (x))

int main()
{
    // Single-line comment

    printf("Hello World\n");

    return 0;
}
```

## 📤 Sample Output

```text
Header included: stdio.h
Header included: myheader.h

Object macro stored: PI
Function macro stored: SQUARE

Preprocessing completed successfully
Output file: input.i
```

*Actual output may vary depending on the input file and implemented features.*

## 📚 Concepts Learned

- C Programming
- File Handling
- String Handling
- File Inclusion
- Macro Processing
- GCC Compilation
- Makefile
- Linux Commands

## 🔮 Future Enhancements

- Implement recursive header file inclusion.
- Implement complete object-like macro expansion.
- Implement function-like macro expansion.
- Support conditional compilation directives.
- Improve error handling.
- Support additional preprocessing directives.

## 👩‍💻 Author

**Lavanya Alugu**

## 📄 License

This project is developed for educational purposes.

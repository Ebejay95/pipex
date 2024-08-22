# pipex

**A project to simulate the functionality of the shell pipeline in C.**

This project implements a simplified version of the shell's pipeline feature, allowing for the execution of commands connected by pipes. It demonstrates proficiency in process creation, file handling, and inter-process communication using pipes.

## Structure

### src/

The `src` directory contains the core implementation files:

- **pipex.c**: The main function handling the execution of commands with pipes, replicating the shell's pipeline behavior.
- **pipex_utils.c**: Utility functions supporting the main program, including functions for string manipulation, error handling, and path management.
- **file_operations.c**: Implements functions for opening, reading, writing, and closing files, ensuring correct file handling in the pipeline.

### includes/

The `includes` directory contains header files:

- **pipex.h**: Declares function prototypes and defines necessary macros for the project.

### Makefile

The Makefile automates the build process, compiling all source files and linking them to create the final executable.

## Features

- **Pipeline Simulation**: Executes commands in a sequence connected by pipes, similar to how a shell pipeline works.
- **File Redirection**: Supports input and output redirection from files, enabling the use of file descriptors in the pipeline.
- **Error Handling**: Robust error handling for common issues such as file access errors and invalid commands.

## Usage

To compile the project, run:

```
make
```

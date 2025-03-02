# Minishell

## Overview
Minishell is a simplified shell implementation based on bash. This project challenges students to recreate a basic command-line interface with core shell functionalities, providing a deep understanding of processes, file descriptors, and signal handling in Unix-like systems.

## Skills & Concepts
- Unix Processes
- Signal Handling
- Parser Implementation
- Memory Management
- File Operations
- Environment Variables
- Error Handling
- Inter-Process Communication

## Built-in Commands
- `echo` with option `-n`
- `cd` with relative or absolute path
- `pwd` without any options
- `export` without any options
- `unset` without any options
- `env` without any options or arguments
- `exit` without any options

## Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/minishell.git

# Navigate to the project directory
cd minishell

# Compile the project
make

# Run the program
./minishell

# Test a simple command inside the shell
minishell$ echo "Hello, Minishell is working!"
```

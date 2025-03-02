# Minishell

## Overview
Minishell is a simplified shell implementation based on bash. This project challenges students to recreate a basic command-line interface with core shell functionalities, providing a deep understanding of processes, file descriptors, and signal handling in Unix-like systems.

## Features

### Command Execution
- Execute commands with arguments
- Handle absolute and relative paths (using PATH environment variable)
- Support for simple commands, pipes, and redirections

### Built-in Commands
- `echo` with option `-n`
- `cd` with relative or absolute path
- `pwd` without any options
- `export` without any options
- `unset` without any options
- `env` without any options or arguments
- `exit` without any options

### Signal Handling
- Handle `Ctrl+C` (SIGINT)
- Handle `Ctrl+D` (EOF)
- Handle `Ctrl+\` (SIGQUIT)

### Line Editing
- Command history (up and down arrows)
- Input editing capabilities

### Advanced Features
- Redirections: `<`, `>`, `<<`, `>>`
- Pipes: `|`
- Environment variables: `$VAR`
- Exit status: `$?`
- Quotes handling (single and double)

## Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/minishell.git

# Navigate to the project directory
cd minishell

# Compile the project
make

# (Optional) Compile with bonus features
make bonus
```

## Usage

```bash
# Run the shell
./minishell
```

## Dependencies

This project requires the readline library:

**For Ubuntu/Debian:**
```bash
sudo apt-get install libreadline-dev
```

**For macOS (using Homebrew):**
```bash
brew install readline
```

## Examples

Once running, you can use minishell like any standard shell:

```bash
minishell$ ls -la
minishell$ echo "Hello World" > output.txt
minishell$ cat < output.txt | grep Hello
minishell$ cd /path/to/directory
minishell$ pwd
minishell$ export VAR=value
minishell$ echo $VAR
minishell$ exit
```

## Learning Outcomes
- Process creation and management
- File descriptor manipulation
- Signal handling
- Parser and lexer implementation
- Command execution logic
- Environment variable management
- Memory management in a complex program

## Author

- Your Name (@your_intra_login)

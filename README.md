# minishell

A simplified Unix shell implementation.

## What is minishell?

minishell is a project designed to replicate a subset of the functionality found in the Bash shell. It aims to provide a practical understanding of how shells operate, including command parsing, execution, and environment management, within specific constraints.

## Key Concepts

* **Parsing User Input:** Breaking down the user's input into commands and arguments.
* **Command Execution:** Executing external commands using `fork` and `execve`.
* **Environment Variable Handling:** Expanding environment variables (e.g., `$PATH`, `$HOME`).
* **Built-in Commands:** Implementing basic built-in commands like `echo`, `cd`, `pwd`, `export`, `unset`, and `exit`.
* **Signal Handling:** Manage signals like CTRL+C and CTRL+\.
* **Redirections:** Handling redirections like <, >, >>.
* **Pipes:** Handling pipes.

## Usage

1.  **Compile:**
    ```bash
    make
    ```
    This will compile the `minishell` executable.
2.  **Run:**
    ```bash
    ./minishell
    ```
    You will then be presented with a prompt, where you can enter commands.

## Key Features

* **Command Execution:** Executes external commands found in the `$PATH`.
* **Environment Variable Handling:** Expands environment variables within commands.
* **Built-in Commands:**
    * `echo`: Displays arguments.
    * `cd`: Changes the current directory.
    * `pwd`: Prints the current working directory.
    * `export`: Sets environment variables.
    * `unset`: Unsets environment variables.
    * `exit`: Exits the shell.
* **Signal Handling:** Manages interrupt signals.
* **Redirections:** Handle input and output redirections.
* **Pipes:** Handle the passing of output of one command to the input of another.

## Implementation Details

* **Parsing:** The input is parsed into tokens and then into a command structure.
* **Execution:** The shell uses `fork` to create child processes and `execve` to execute commands.
* **Environment:** The shell maintains an environment variable list.
* **Error Handling:** Basic error handling is implemented to manage invalid commands and syntax.

## Notes

* This project provides a hands-on understanding of how shells work.
* It demonstrates skills in parsing, process management, and environment manipulation.
* This project pushes your ability to understand and implement complex C programs.

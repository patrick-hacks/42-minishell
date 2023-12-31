# 42-Minishell

## Project Description

This is the Minishell project for the 42 school curriculum. The goal of this project is to create a simple shell, capable of handling basic command-line operations. The Minishell project is designed to deepen your understanding of processes, file descriptors, and basic shell functionality.

## Features

- **Command Execution:** Minishell can execute simple commands with or without arguments.
- **Redirection:** Support for input and output redirection (>, <).
- **Pipes:** Ability to handle multiple commands connected by pipes (|).
- **Environment Variables:** Implement basic support for environment variables like $HOME, $PWD, etc.
- **Signals:** Minishell should handle signals (Ctrl-C, Ctrl-D, etc.) appropriately.
- **Line Editing:** Use the GNU Readline library to provide basic line editing capabilities.
- **Error Handling:** Implement error handling and display meaningful error messages.

## Getting Started

### Prerequisites

- GCC compiler
- GNU Make
- Readline library

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/42-minishell.git
    ```

2. Change into the project directory:

    ```bash
    cd 42-minishell
    ```

3. Build the project:

    ```bash
    make
    ```

4. Run Minishell:

    ```bash
    ./minishell
    ```

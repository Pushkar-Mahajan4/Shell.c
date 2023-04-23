### Simple Shell

This is a simple shell program written in C language. The program provides a basic command-line interface where users can enter commands to be executed. The program also maintains a history of commands entered by the user, which can be accessed using the "history" command. Additionally, the program supports some basic shell functionalities, including background processes and job management.

## Requirements

Linux operating system
GCC compiler
Standard C libraries
Compilation
To compile the program, open the terminal and navigate to the directory containing the source code. Then, use the following command to compile the code:

    gcc -o shell shell.c

This will create an executable file named "shell".

## Usage

To start the shell, navigate to the directory containing the executable file and use the following command:

    ./shell

This will launch the shell, and you can start entering commands. The shell supports the following commands:

## exit: This command will exit the shell.

1. history: This command will display the list of commands entered in the current session.
2. !!: This command will execute the last command entered by the user.
3. !n: This command will execute the nth command in the command history. Replace "n" with the index of the command in the history list.
4. jobs: This command will display a list of currently running background jobs.
5. To run a command, simply enter the command in the shell and press Enter. If the command requires any arguments, enter them separated by spaces. To run a command in the background, append an ampersand (&) at the end of the command.

Limitations

1. The shell program does not support advanced shell functionalities such as I/O redirection and piping.
2. The program is not designed for use in a production environment and may have security vulnerabilities.

## Author

This program was written by Pushkar Mahajan.

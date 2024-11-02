# Lubaba's Shell
# Overview
Lubaba's Shell is a simple command-line shell implemented in C that demonstrates key concepts in system programming, such as process management, command execution, input/output redirection, and job control. It allows users to execute commands, maintain a command history, and manage background jobs.

# Features
Command Execution: Execute shell commands using execvp.
Command History: Store and recall the last 10 commands entered by the user.
Input/Output Redirection: Support for < and > to redirect input and output.
Pipes: Ability to pipe the output of one command to the input of another using |.
Job Control: Support for running commands in the background with &, and managing background jobs.
Built-in Commands: Implement built-in commands like cd, exit, jobs, kill, and help.


# Limitations
Signal Handling: The shell does not handle all signals robustly, which can lead to zombie processes if not managed correctly.
Input Validation: Insufficient validation for user inputs can lead to unexpected behavior, especially with commands like kill and cd.
Error Handling: Some functions may not return meaningful errors to the user, making it difficult to diagnose issues.
Memory Management: The current implementation has potential memory leaks, especially in the command history management.
Command Length and Argument Limits: There are hard-coded limits on the length of commands and the number of arguments, which may restrict usage.

# Error Handling
Forking Errors: If fork() fails, the program prints an error message and exits.
Execution Errors: If execvp() fails, it prints an error message indicating that the command was not found.
File I/O Errors: When opening files for redirection, the shell prints an error message if the file cannot be opened.
Job Management: The shell checks for valid job numbers before attempting to kill a background job, printing an error if the job number is invalid.
# Code Organization
Main Loop: The shellLoop function manages the main input loop, displaying prompts and processing user commands.
Command Parsing: The parseCommand function tokenizes the input string into an array of arguments for execution.
Execution Functions:
executeBuiltInCommand: Handles built-in commands like cd, exit, jobs, kill, and help.
executeExternalCommand: Forks a child process to execute external commands and manages background processes.
History Management: Commands are added to a history array with a maximum size of 10, allowing retrieval of recent commands.
Signal Handling: The shell sets up a signal handler for SIGCHLD to clean up zombie processes.
# Usage
Compilation: Compile the shell using gcc -o lubabashell lubabashell.c.
Running the Shell: Execute the shell with ./lubabashell.
Commands: Use commands like ls, pwd, cd <directory>, and exit. To run in the background, append & to the command.
History: Access previous commands using !! to repeat the last command or !n for the nth command in history.

# Conclusion
Lubaba's Shell is a foundational project for understanding shell operations and system programming in C. While it provides essential features for command execution and job management, improvements can be made in error handling, memory management, and user input validation to enhance usability and robustness.

# Unix-Like Shell

A Unix-like command-line shell implemented in **C++** for Linux using **POSIX system calls and process-management APIs**.

The project is being developed from the ground up to understand how Unix shells work internally, particularly how they create and manage processes, connect commands through pipelines, handle files and signals, and manage foreground/background jobs.

> **Project Status:** In Development  
> **Current Milestone:** M11 — Job Control  
> **Language:** C++17  
> **Platform:** Linux / WSL2  
> **Build System:** CMake

---

## 1. About the Project

A shell is one of the most fundamental components of a Unix-like operating system. It provides an interface between the user and the operating system by interpreting commands and managing the processes required to execute them.

Instead of relying on an existing shell such as Bash, this project implements a simplified Unix-like shell from scratch.

The shell currently supports command execution, built-in commands, pipelines, input/output redirection, background processes, environment variables, command history, quoting, escaping, variable expansion, process groups, and basic job management.

The project is being developed incrementally so that each feature can be understood, implemented, tested, and committed independently.

---

## 2. Why This Project?

The primary goal of this project is to gain practical understanding of **Linux systems programming and operating-system concepts** by implementing functionality normally provided by a Unix shell.

The project provides hands-on experience with:

- Process creation and termination
- Parent-child process relationships
- Program execution using `exec`
- Inter-process communication
- File descriptors
- Pipes
- Input/output redirection
- Signals
- Process groups
- Background processes
- Job management
- Terminal-related process control
- Unix/POSIX APIs

Rather than treating these concepts only as theoretical operating-system topics, the project uses them in a working systems program.

---

## 3. Project Objectives

The main objectives are to:

1. Implement a functional Unix-like command-line shell.
2. Understand how a shell creates and manages processes.
3. Implement command pipelines using Unix pipes.
4. Implement input and output redirection using file descriptors.
5. Support foreground and background process execution.
6. Implement Unix-style job management.
7. Understand and handle POSIX signals.
8. Implement process groups for multi-process jobs.
9. Implement foreground/background job control.
10. Develop the project using a modular and maintainable C++ architecture.
11. Test and document the shell as features are added.

---

## 4. Technology Stack

### Programming Language

- **C++17**

### Operating System / Environment

- Linux
- Ubuntu
- WSL2

### System Programming APIs

- POSIX APIs
- Unix system calls
- Process management APIs
- Signal APIs
- File descriptor APIs

### Important APIs Used

```text
fork()
execvp()
waitpid()
pipe()
dup2()
open()
close()
chdir()
getcwd()
getenv()
setenv()
unsetenv()
setpgid()
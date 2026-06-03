# POSIX Signal Handling — Inter-Process Communication

A multi-process C program demonstrating IPC using POSIX signals.

The parent process forks two child processes, each running a loop
and printing its status every 2 seconds. Each child registers a
custom SIGUSR1 handler. After 5 seconds, the parent sends SIGUSR1
to both children, triggering a graceful shutdown via the handler
functions. waitpid() prevents zombie processes.

## Compilation

gcc -std=c99 -Wall -o ipc my_ipc_signal.c

## Usage

./ipc

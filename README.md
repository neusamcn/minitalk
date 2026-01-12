*This project has been created as part of the 42 curriculum by ncruz-ne.*

## Description

The goal is to build a small message-passing system where a client program sends a string to a server program, using only UNIX signals as the communication mechanism.
We could also call this a custom inter-process communication (IPC) protocol on top of UNIX signals.



## Instructions

1. Compile the project with `make all`.
2. Open 2 terminal windows at the root of the project folder.
3. From one window we'll start the server program: `./server`
4. In the other window we start the client program, adding the PID that was provided by `./server` and a message, as following: `./client server_PID "message"`
5. Confirm message was received.



## Resources

AI was used as a support for research in order to find and better understand the most relevant resources and concepts related to this project.

#### Signals

- https://man7.org/linux/man-pages/man7/signal.7.html
- https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/signal.h.html
- https://man7.org/linux/man-pages/man2/sigaction.2.html
- https://pubs.opengroup.org/onlinepubs/007904875/functions/sigaction.html
- https://pubs.opengroup.org/onlinepubs/9799919799/
- https://pubs.opengroup.org/onlinepubs/9799919799/functions/sigemptyset.html#

#### kill()

- https://man7.org/linux/man-pages/man2/kill.2.html

#### pause()

- https://man7.org/linux/man-pages/man2/pause.2.html

#### usleep()

- https://man7.org/linux/man-pages/man3/usleep.3.html

#### Process IDs

- https://man7.org/linux/man-pages/man2/getpid.2.html
- https://man7.org/linux/man-pages/man5/proc_sys_kernel.5.html

#### Interprocess Communication overview

- https://man7.org/linux/man-pages/man7/ipc.7.html

#### Bitwise operations

- https://www.geeksforgeeks.org/c/bitwise-operators-in-c-cpp/
# Network Programming Project

This project demonstrates a simple client-server application using TCP sockets in C.

## Files

- `server.c`: Contains the server-side code.
- `client.c`: Contains the client-side code.
- `constants.c` and `constants.h`: Contains utility functions and definitions used by both the client and server.

## Compilation

To compile the project, you can use the provided `Makefile`. Run the following command in the project directory:

```sh
make all
```

# Usage

## Server

To run the server, use the following command:

```sh
./server port-number-to-listen-over
```
The server will bind to the specified IP address and port, and listen for incoming connections.

## Client

To run the client, use the following command:

```sh
./client ip-address-target-device port-number-of-target-device
```

The client will connect to the server at the specified IP address and port. You can then enter messages to send to the server. Type exit to end the client session.

## Clean Up

To clean up the compiled files, run:

```sh
make clean
```
This will remove the object files and executables.

License
This project is licensed under the MIT License.
Feel free to modify the content as per your project's specific details and requirements.
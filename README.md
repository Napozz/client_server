# TCP Echo Server Documentation

## Overview

This program implements a basic TCP echo server that listens on a specified port and echoes bback any messages received from clients. The server will continue running until it receives the "NAPOZZ" command from a client.

## Usage

```sh
./server <PORT>
```
````

### Arguments

- `PORT`: The port number to listen on (required)
- `-h`: Display help message

### Example

```sh
./server 8080
```

## Features

- Single client connection handling
- Echo functionality (sends back received messages)
- Clean shutdown with "NAPOZZ" command
- Support for IPv4 connections
- Buffer size of 80 bytes

# Network Tools Documentation

This project consists of three C programs that demonstrate basic network communication:

1. **MyHost** - DNS lookup tool
2. **Server** - TCP server implementation
3. **Client** - TCP client implementation

## Building the Project

Compile each program using gcc:

```bash
gcc -o myhost myhost.c
gcc -o server server.c
gcc -o client client.c
```

## MyHost Tool (myhost.c)

A simple DNS lookup tool that resolves hostnames to IP addresses.

### Usage:

```bash
./myhost <hostname>
```

Example:

```bash
./myhost google.fr
```

Options:

- `-h` : Display help message

## Server (server.c)

A TCP server that listens for incoming connections and echoes back received messages.

### Usage:

```bash
./server <PORT>
```

Example:

```bash
./server 8080
```

The server will:

1. Listen on the specified port
2. Accept one client connection
3. Echo back any received messages
4. Close when receiving "NAPOZZ" command

## Client (client.c)

A TCP client that can connect to the server and send messages.

### Usage:

```bash
./client <URL:PORT>
```

Example:

```bash
./client localhost:8080
```

The client will:

1. Connect to the specified server
2. Allow you to type messages to send
3. Display server responses
4. Close connection when sending "NAPOZZ"

## Protocol

- Communication uses TCP sockets
- Messages are text-based
- Special command "NAPOZZ" terminates the connection
- Server echoes back all received messages

## Error Handling

All programs include basic error handling for:

- Invalid arguments
- Connection failures
- Network errors
- Invalid hostnames

### File `myhost.c`

This program resolves hostnames to IP addresses, supporting both IPv4 and IPv6.

##### Libraries Used

- `stdio.h`: Standard I/O operations
- `string.h`: String manipulation functions
- `netdb.h`: Network database operations (DNS lookups)
- `arpa/inet.h`: Internet operations (IP address conversions)

#### Key Components

##### Header Files Purpose

```c
#include <stdio.h>    // printf(), etc
#include <string.h>   // strcmp(), etc
#include <netdb.h>    // getaddrinfo()
#include <arpa/inet.h> // inet_ntop()
```

##### Main Functions

1. `help()`: Displays usage instructions with ASCII art
2. `main()`: Entry point that:
   - Accepts hostname as command line argument
   - Handles -h flag for help
   - Performs DNS lookup (implementation not shown in visible code)

#### Usage Examples

```bash
# Get help
./myhost -h

# Lookup hostname
./myhost google.fr
```

#### What It Does

1. Takes a hostname as input
2. Uses DNS resolution to find IP addresses
3. Displays both IPv4 and IPv6 addresses if available
4. Shows ASCII art error message if no argument provided

Note: The visible code section doesn't show the actual DNS resolution implementation, which would typically use `getaddrinfo()` from the `netdb.h` library.

### File `client.c`

#### Build Steps

1. Create TCP socket client
2. Parse server address and port from args
3. Connect to server
4. Enter command loop
5. Send/receive data until "NAPOZZ" command
6. Clean up and exit

#### Libraries Used

```c
#include <arpa/inet.h>  // inet_addr()
#include <stdio.h>      // printf(), scanf()
#include <string.h>     // strcmp()
#include <sys/socket.h> // socket(), connect()
#include <unistd.h>     // read(), write(), close()
```

#### Program Documentation

##### Usage

```bash
./client <IP_ADDRESS:PORT>

# Example
./client 127.0.0.1:8080
```

##### Features

- Connects to TCP server
- Interactive command input
- Receives and displays server responses
- Buffer size: 80 bytes for commands, 255 bytes for responses
- Special command "NAPOZZ" exits program
- Shows connection status
- Error handling for connection failures

##### Protocol

- Text-based command/response
- Commands limited to 80 bytes
- Server responses limited to 255 bytes
- "NAPOZZ" is reserved shutdown command

##### Error Handling

- Invalid arguments
- Connection failures
- Socket creation errors

The program implements a basic TCP client that connects to a server, sends commands, and displays responses until terminated with "NAPOZZ".

### File `server.c`

#### Steps

1. Parse command line args for port
2. Create TCP socket
3. Bind to specified port
4. Listen for connections
5. Accept client connection
6. Echo loop until "NAPOZZ"
7. Clean shutdown

#### Technical Details

##### Libraries

```c
#include <arpa/inet.h>   // Socket functions
#include <sys/socket.h>  // Socket API
#include <string.h>      // String operations
#include <unistd.h>      // System calls
```

##### Core Components

- Socket binding: Port
- Connection handling: Single client
- Buffer size: 80 bytes
- Protocol: Text-based echo
- Termination: "NAPOZZ" command

##### Build & Run

```bash
# Compile
gcc -o server server.c

# Run (example on port 8080)
./server 8080
```

##### Socket Flow

1. Create socket (`socket()`)
2. Bind to port (`bind()`)
3. Listen (`listen()`)
4. Accept connection (`accept()`)
5. Echo loop (`recv()`/`send()`)
6. Close (`close()`)

##### Error Handling

- Socket creation fails
- Bind fails
- Listen fails
- Accept fails
- Send/Receive fails

The server implements a basic TCP echo service that reflects back client messages until receiving "NAPOZZ".

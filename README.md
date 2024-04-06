IRC Server (ircserv)
Overview

This project is a C++ 98 implementation of an IRC (Internet Relay Chat) server. IRC is a text-based communication protocol used for instant messaging over the internet. The server allows users to connect, communicate in real-time through channels, and exchange private messages.
Pedagogical Objectives

<ul>
<li>Concurrency and Non-blocking I/O: Learn techniques for handling multiple client connections simultaneously without blocking using non-blocking I/O operations.</li>
<li>C++ Language Features: Practice C++ programming, adhering to the C++ 98 standard, and utilizing features such as sockets, file descriptors, and string manipulation.</li>
<li>Software Development Best Practices: Apply software development best practices such as modular programming, code organization, and adherence to coding standards.</li>
<li>System Calls and Error Handling: Explore system calls for network operations, error handling mechanisms, and troubleshooting techniques.</li>
</ul>


How to Use

Compilation: Compile the source code using the provided Makefile with the make command.
Execution: Run the compiled binary with the appropriate command-line arguments (<port> and <password>).

    ./ircserv <port> <password>
    <port>: The port number on which the server will listen for incoming connections.
    <password>: The password required for client authentication.

Connecting Clients: Clients can connect to the server using IRC client software and specifying the server's address, port, and password.
Communication: Once connected, users can communicate with each other in real-time through channels or private messages as per IRC protocol specifications.

/*
 * File: octopus_ipc_socket.hpp
 * Organization: Octopus
 * Description:
 *  This header file defines the `Socket` class, which encapsulates the functionalities required to
 *  manage communication through a Unix Domain Socket (UDS). It includes methods for setting up a
 *  server to handle incoming client requests, sending responses, and performing arithmetic operations.
 *  The class also supports client-side socket communication by providing methods for connecting to the
 *  server, sending queries, and receiving responses.
 *
 * Includes:
 *  - Socket setup and connection management through Unix domain sockets.
 *  - Query and response handling for arithmetic operations.
 *  - Server-side socket functions including binding, listening, and accepting client connections.
 *  - Client-side socket functions including query sending and response receiving.
 *
 * Author		: [ak47]
 * Organization	: [octopus]
 * Date Time	: [2025/0313/21:00]
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <chrono>
#include <thread>
#include <vector>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <iomanip>

#include "octopus_ipc_cmd.hpp"
/////////////////////////////////////////////////////////////////////////////////////////////////////////

class Socket
{
private:
    // Socket definitions
    const char *socket_path;  // Path of the Unix domain socket
    int socket_fd;            // Socket file descriptor

    int domain;               // Domain for the socket (AF_UNIX)
    int type;                 // Type of socket (SOCK_STREAM)
    int protocol;             // Protocol used (0 for default)

    // Server-related definitions
    int max_waiting_requests; // Maximum number of pending requests
    sockaddr_un addr;        // Address for the socket

    // Query and response definitions
    int operation;            // Operation to be performed (e.g., addition, subtraction)
    int number1;              // First operand for the arithmetic operation
    int number2;              // Second operand for the arithmetic operation
    int result;               // Result of the arithmetic operation
    ssize_t query_bytesRead;  // Bytes read from the query
    ssize_t resp_bytesRead;   // Bytes read from the response
    
public:
    // Query and response buffer sizes
    int query_buffer_size;    // Size of the query buffer
    int respo_buffer_size;    // Size of the response buffer

    // Constructor
    Socket();

    // Socket-related functions
    int open_socket();  // Open the socket
    int close_socket(); // Close the socket

    // Server-side functions
    void bind_server_to_socket();     // Bind the socket to the specified address
    void start_listening();           // Start listening for incoming client connections
    int wait_and_accept();            // Wait for a client connection and accept it
    int send_response(int client_fd, std::vector<int> &resp_vector);  // Send a response to the client
    int send_buff(int client_fd, char *resp_buffer,int length);
    std::vector<int> get_query(int client_fd);  // Retrieve the query from the client

    // Client-side functions
    int connect_to_socket();               // Connect to the server socket
    void send_query(std::vector<int> &query_vector);  // Send a query to the server
    std::pair<std::vector<int>, int> get_response();       // Retrieve the response from the server

    void printf_vector_bytes(const std::vector<int> &vec, int length);
    void printf_buffer_bytes(const std::vector<int> &vec, int length);
    void printf_buffer_bytes(const void *buffer, int length);
};

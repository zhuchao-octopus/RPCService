#include "octopus_ipc_socket.hpp"


int main(int argc, char* argv[]) 
{
    int socket_client;
    Socket client;
    int operation;
    int number1;
    int number2;

    std::vector<int> query_vector;
    std::vector<int> response_vector;

    socket_client=client.open_socket();
    socket_client=client.connect_to_socket();

    if(socket_client <0)
    {
        std::cerr << "Client: Invalid socket of connection" << std::endl;
        client.close_socket();
        std::exit(-1); 
    }
    else
    {
        std::cout << "Client: open a socket [" << socket_client << "] connected to server"  << std::endl;
    }

    if (argc != 4) {
        std::cerr << "Client: Invalid number of arguments" << std::endl;
        client.close_socket();
        std::exit(-1);
    }

    if (strcmp(argv[1], "add") == 0)
    {
        operation = 1;
    }
    else if (strcmp(argv[1], "subtract") == 0)
    {
        operation = 2;
    }
    else if (strcmp(argv[1], "multiply") == 0)
    {
        operation = 3;
    }
    else if (strcmp(argv[1], "divide") == 0)
    {
        operation = 4;
    }
    else {
        std::cerr << "Client: Invalid operation." << std::endl;
        client.close_socket();
        std::exit(-1);
    }

    try {
        number1 = std::stoi(argv[2]);
        number2 = std::stoi(argv[3]);
    }
    catch (const std::exception& e) {
        std::cerr << "Client: Error while parsing arguments: " << e.what() << std::endl;
        client.close_socket();
        std::exit(-1);
    }

    std::cout << "Client: Sending query: " << operation << " " << number1 << " " << number2 << std::endl;
    
    query_vector = {operation, number1, number2};
    client.send_query(query_vector);

    response_vector = client.get_response();
    std::cout << "Client: Received response: " << response_vector[0] << std::endl;

    client.close_socket();

    return 0;
}
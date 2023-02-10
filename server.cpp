// // include needed header files to use sockets 
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <iostream>
// #include <string>

// // int main ()
// // {
// //     struct sockaddr_in server;

// //     int sock , conx_sock , n;
// //     char buffer[1024];

// //     sock = socket(AF_INET, SOCK_STREAM, 0);
// //     if (sock < 0)
// //     {
// //         perror("socket");
// //         exit(1);
// //     }

// //     server.sin_family = AF_INET;
// //     server.sin_port = htons(6969);
// //     server.sin_addr.s_addr = htonl(INADDR_ANY);

// //     if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
// //     {
// //         perror("bind");
// //         exit(2);
// //     }

// //     if (listen(sock, 5) == -1)
// //     {
// //         perror("listen");
// //         exit(3);
// //     }

// //     for (;;)
// //     {
// //         conx_sock = accept(sock, NULL, NULL);
// //         if (conx_sock ==0)
// //         {
// //             printf("Connection accepted , socker fd is %d ,\n", conx_sock);
// //             // perror("accept");
// //             // exit(4);
// //         }

// //         // while ((n = read(conx_sock, buffer, 1024)) > 0)
// //             // write(1, buffer, n);

// //         if (n == -1)
// //         {
// //             perror("read");
// //             exit(5);
// //         }
// //         if (close(conx_sock) == -1)
// //         {
// //             perror("close");
// //             exit(6);
// //         }
// //     }



// // }





// int main ()
// {
//     sockaddr_in addr;
//     int n , sock , conx;
//     std::string buffer;

//     sock = socket(AF_INET, SOCK_STREAM, 0);
//     if (sock < 0)
//     {
//         perror("socket");
//         exit(1);
//     }

//     addr.sin_family = AF_INET;
//     addr.sin_port = htons(1234);
//     addr.sin_addr.s_addr = htonl(INADDR_ANY);

//     if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
//     {
//         perror("bind");
//         exit(2);
//     }

//     if (listen(sock, 5) == -1)
//     {
//         perror("listen");
//         exit(3);
//     }

//     for (;;)
//     {
//         conx  = accept(sock, NULL, NULL);
//         if (conx == -1)
//         {
//             perror("accept");
//             exit(4);
//         }
//         else
//         {
//             printf("Connection accepted , socker fd is %d ,\n", conx);
//         }

//         while (getline(std::cin, buffer))
//         {
//             write(conx, buffer.c_str(), buffer.size());
//         }

//         // if (close(conx) == -1)
//         // {
//             // perror("close");
//             // exit(6);
//         // }

//     }





// }


#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int PORT = 6969;

int main() {
  int server_socket, client_socket;
  sockaddr_in server_address, client_address;
  socklen_t client_address_len = sizeof(client_address);
  char buffer[1024];

  // Create the server socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // Set up the server address
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(PORT);

  // Bind the server socket to the address
  if (bind(server_socket, (sockaddr*) &server_address, sizeof(server_address)) < 0) {
    std::cerr << "Error binding socket" << std::endl;
    return 1;
  }

  // Listen for incoming connections
  if (listen(server_socket, 5) < 0) {
    std::cerr << "Error listening on socket" << std::endl;
    return 1;
  }

  // Accept incoming connections
  while (true) {
    client_socket = accept(server_socket, (sockaddr*) &client_address, &client_address_len);
    if (client_socket < 0) {
      std::cerr << "Error accepting connection" << std::endl;
      return 1;
    }

    // Read from the client socket
    int bytes_received = read(client_socket, buffer, 1024);
    if (bytes_received < 0) {
      std::cerr << "Error reading from socket" << std::endl;
      return 1;
    }

    // Write the message to the terminal
    std::cout << "Received message: " << buffer << std::endl;

    // Close the client socket
    close(client_socket);
  }

  return 0;
}
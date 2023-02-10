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
// #include <sstream>

// // int main ()
// // {
// //     struct sockaddr_in addr;
// //     int n , sock , conx_sock;
// //     char buffer[1024];


// //     sock = socket(AF_INET, SOCK_STREAM, 0);
// //     if (sock < 0)
// //     {
// //         perror("socket");
// //         exit(1);
// //     }

// //     addr.sin_family = AF_INET;
// //     addr.sin_port = htons(6969);
// //     addr.sin_addr.s_addr = htonl(INADDR_ANY);

// //     connect(sock, (struct sockaddr *)&addr, sizeof(addr));
// //     if (conx_sock == -1)
// //     {
// //         perror("connect");
// //         exit(2);
// //     }


// //     // while ((n = read(STDIN_FILENO, buffer, 1024)) > 0) 
// //         write(sock, "buffer\n", n);

// //     if (n == -1)
// //     {
// //         perror("read");
// //         exit(3);
// //     }

// //     if (close(sock) == -1)
// //     {
// //         perror("close");
// //         exit(4);
// //     }

// //     // exit(0);



// // }



// int main ()
// {
//     sockaddr_in addr;
//     int n , sock , conx_sock;
//     char buffer[1024];

//     sock = socket(AF_INET, SOCK_STREAM, 0);
//     if (sock < 0)
//     {
//         perror("socket");
//         exit(1);
//     }

//     addr.sin_family = AF_INET;
//     addr.sin_port = htons(1234);
//     addr.sin_addr.s_addr = htonl(INADDR_ANY);

//     conx_sock = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
//     if (conx_sock == -1)
//     {
//         perror("connect");
//         exit(2);
//     }
//     else
//     {
//         printf("Connection accepted , socket fd is %d ,\n", conx_sock);
//     }

//     write(sock, "buffer\n", 7);

//     if (close(sock) == -1)
//     {
//         perror("close");
//         exit(4);
//     }

// }
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

const char* SERVER_IP = "0.0.0.0";
const int PORT = 6969;

int main() {
  int client_socket;
  sockaddr_in server_address;
  char message[1024];

  // Create the client socket
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // Set up the server address
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
//   inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

  // Connect to the server
  if (connect(client_socket, (sockaddr*) &server_address, sizeof(server_address)) < 0) {
    std::cerr << "Error connecting to server" << std::endl;
    return 1;
  }

  // Read a message from the user
  std::cout << "Enter a message to send: ";
  std::cin.getline(message, 1024);

  // Send the message to the server
  int bytes_sent = write(client_socket, message, strlen(message));
  if (bytes_sent < 0) {
    std::cerr << "Error writing to socket" << std::endl;
    return 1;
  }

  // Close the client socket
  close(client_socket);

  return 0;
}
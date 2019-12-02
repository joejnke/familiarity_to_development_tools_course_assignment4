#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
// #define port_num 8888
#define host "localhost"

void client_report(const char* msg, int terminate) {
  perror(msg);
  if (terminate) exit(-1); /* failure */
}

void client_close_connection(int fd) {
    puts("server closing connection ...");
    close(fd);
    puts("server connection closed...");
}

int init_client(int port_number) {
    char server_msg[100];
    int server_msg_size;
    // initialize a file descriptor for the client 
    puts("initializing client fd ...");    
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    // report and exit if failed to initialize file descriptor
    if (client_fd < 0) client_report("clinet fd", 1);

    // get the address of the host
    puts("obtaining host address ...");
    struct hostent* hptr = gethostbyname(host); /* localhost: 127.0.0.1 */ 
    if (!hptr) client_report("gethostbyname", 1); /* is hptr NULL? */
    if (hptr->h_addrtype != AF_INET)       /* versus AF_LOCAL */
        client_report("bad address family", 1);

    // configure server address
    puts("configuring server address ...");
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); // clear the content of the variable
    server_addr.sin_family = AF_INET; // network sockets family instead of IPC socket
    server_addr.sin_addr.s_addr = ((struct in_addr*) hptr->h_addr_list[0])->s_addr; // s_addr of the host
    server_addr.sin_port = htons(port_number); // server port address converted to network byte order (big-endian)

    // connect to the server
    // report and exit if failed to connect
    puts("connecting to server ...");
    if (connect(client_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        client_report("connect", 1);
        
    fprintf(stderr, "successfully connected on port %i ...\n", port_number);
    read(client_fd, &server_msg_size, sizeof(int)); // get size
    read(client_fd, server_msg, server_msg_size); //get message
    printf("\nServer: %s\n", server_msg); // echo server's initial messeg
    return client_fd;
}

void request_server(int client_fd) {
    int client_msg_size;
    int file_size;
    // send request until the user passes exit
    char file_name[50];
    scanf("%s", file_name); // accept filename from user
    // while(strcmp(file_name, "exit") != 0){
        // send file name size
        client_msg_size = sizeof(file_name);
        write(client_fd, &client_msg_size, sizeof(int));
        // send file name to server
        write(client_fd, file_name, sizeof(file_name));

        printf("\nClient: %s", file_name);

        // read in the file content sent from the server
        // read file size
        read(client_fd, &file_size, sizeof(int));
        // read file content
        char file_content[file_size];
        read(client_fd, file_content, file_size);
        printf("\nServer: \n%s\n", file_content); // print out file content

    //     puts("Type in another file name ...");
    //     scanf("%s", file_name); // accept filename from user
    // }    

    client_close_connection(client_fd);
}

// int main() {
//     int client_fd = init_client(8888);
//     request_server(client_fd);
//     return 0;
// }

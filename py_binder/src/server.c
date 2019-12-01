#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "clieserv_helper.h"

#define port_num 8888

int init_server(int port_number) {
    // initialize a file descriptor for the server 
    puts("initializing server fd ...");
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // report and exit if failed to initialize file descriptor
    if (server_fd < 0) report("socket", 1);

    // initialize address for the server
    puts("initializing server address ...");
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); // clear the content of the variable
    server_addr.sin_family = AF_INET; // network sockets family instead of IPC socket
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // convert byte order to network byte order (big-endian)
    server_addr.sin_port = htons(port_number); // server port address converted to network byte order (big-endian)

    // bind server's socket file descriptor to the server address
    // report and exit if bind fails
    puts("binding server fd with server address ...");
    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0 )
        report("bind", 1);
    
    return server_fd;
}

void start_server(int server_fd) {
    char *files_dir = getenv("HOME");
    puts(files_dir);
    char init_msg[] = "Type in file name ...";
    char no_file_name_err[] = "No file name given ...";
    char file_not_found[] = "file not found ...";
    int client_msg_size;

    // listen for maximum of 10 connections from client sockets
    // report and exit if listen fails
    if (listen(server_fd, 10) < 0 )
        report("listen", 1);
    
    fprintf(stderr, "Listening on port %i for clients...\n", port_num);

    // handel client's request
    while(1){
        // setup client
        struct sockaddr_in client_addr; /* client address */
        int len = sizeof(client_addr);  /* address length could change */

        // accept connections from a client
        // report and continue to accept next connection if failed to connect with current client
        int client_fd = accept(server_fd, (struct sockaddr*) &client_addr, &len);
        if (client_fd < 0) {
            report("accept", 0); 
            continue;
        }

        // process client's request
        // add a while loop that waits untill the client closes the connection
        // if the client didn't closed the connection, wait to receive another file name
        fprintf(stdout, "connected to client ...\n"); //, client_addr.sin_addr);
        int msg_size = sizeof(init_msg);
        printf("\nServer: %s", init_msg);
        write(client_fd, &msg_size, sizeof(int)); // send message size
        write(client_fd, init_msg, sizeof(init_msg)); // write out initial server messege

        // get file name size
        read(client_fd, &client_msg_size, sizeof(int));
        char file_name[client_msg_size];

        // get file name
        int count = read(client_fd, file_name, sizeof(file_name));
        printf("\nClient: %s\n", file_name);

        // if file name is given
        if (count > 0){
            puts("\nvalid name given....");
            // change working directory
            if (chdir(files_dir) < 0){
                puts("unable to change dir");
                report("change directory", 0);
                close_connection(client_fd);
            }

            // check if such file exists and send the file
            FILE *requested_file;
            requested_file = fopen(file_name, "r");
            // if file is not found 
            if (requested_file == NULL){
                puts("file not found....");
                msg_size = sizeof(file_not_found);
                write(client_fd, &msg_size, sizeof(int)); // send message size
                write(client_fd, file_not_found, sizeof(file_not_found));
                close_connection(client_fd);
            }

            // if file is found
            else {
                puts("file found....");
                // send file size
                fseek(requested_file, 0, SEEK_END);
                int file_size = ftell(requested_file); // obtain file size
                fseek(requested_file, 0, SEEK_SET);
                write(client_fd, &file_size, sizeof(int));
                char file_content[file_size];
                fread (file_content, file_size, 1, requested_file);
                // send file
                write(client_fd, file_content, sizeof(file_content));
                puts("file sent ...");
                // close connection
                close_connection(client_fd);
            }
        }

        // if no file name is given
        else{
            puts("\nno file name given....");
            msg_size = sizeof(no_file_name_err);
            write(client_fd, &msg_size, sizeof(int)); // send message size
            write(client_fd, no_file_name_err, sizeof(no_file_name_err)); // send message
            close_connection(client_fd); // close connection
        }
    } 
}

// int main() {   
//     int server_fd = init_server(8888); //initialize and bind server fd to adress 
//     start_server(server_fd);
//   return 0;
// }

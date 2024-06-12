#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>


//int init_server();
//int accept_connection(int sockfd);

int main(){
    //init_server();

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(9999);
    address.sin_addr.s_addr = 0;

    bind(socketfd, (struct socketaddr*)&address, sizeof(address));

    //listen for incoming messages
    listen(socketfd, 5);
    printf("Waiting for connection!\n");

    //Chat-GPT generated code
    // Set the socket to non-blocking mode
    //fcntl(socketfd, F_SETFL, O_NONBLOCK);

    int clientfd = accept(socketfd, 0, 0);
    printf("Connected!\n");

    struct pollfd fds[2] = {
        {
            0,
            POLLIN,
            0
        },
        {
            clientfd,
            POLLIN,
            0
        }
    };

    for(;;){
        char buffer[256];
        poll(fds, 2, 50000);

        if(fds[0].revents & POLLIN){
            read(0, buffer,255);
            send(clientfd, buffer, 255, 0);
        }
        else if(fds[1].revents & POLLIN) {
            recv(clientfd, buffer, 255, 0);
            printf("%s\n", buffer);
        }
    }
}

/*
int init_server(){
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(9999);
    address.sin_addr.s_addr = 0;

    bind(socketfd, &address, sizeof(address));

    //listen for incoming messages
    int listen_value = listen(socketfd, 5);
    printf("Listen: %d\n", listen_value);

    if(listen_value == -1){
        printf("Listen was not successful.\n");
    }

    //Chat-GPT generated code
    // Set the socket to non-blocking mode
    fcntl(socketfd, F_SETFL, O_NONBLOCK);

    //int clientfd = accept(socketfd, 0, 0);
    int clientfd = accept_connection(socketfd);
    printf("Accept: %d\n", clientfd);
    if(clientfd == -1){
        printf("Connection was not accepted.\n");
    }

    return socketfd;
}

int accept_connection(int sockfd){
    return accept(sockfd, 0, 0);
}
*/
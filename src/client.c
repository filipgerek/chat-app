#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

int main(){
    //init_server();

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(9999);
    address.sin_addr.s_addr = 0;

    connect(socketfd, &address, sizeof(address));

    //Chat-GPT generated code
    // Set the socket to non-blocking mode
    fcntl(socketfd, F_SETFL, O_NONBLOCK);


    struct pollfd fds[2] = {
            {
                    0,
                    POLLIN,
                    0
            },
            {
                    socketfd,
                    POLLIN,
                    0
            }
    };

    for(;;){
        char buffer[256];
        poll(fds, 2, 50000);

        if(fds[0].revents & POLLIN){
            read(0, buffer,255);
            send(socketfd, buffer, 255, 0);
        }
        else if(fds[1].revents & POLLIN) {
            recv(socketfd, buffer, 255, 0);
            printf("%s\n", buffer);
        }
    }
}
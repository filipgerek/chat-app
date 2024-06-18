#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>

int main(){
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(9999);
    address.sin_addr.s_addr = 0;

    connect(socketfd, (struct sockaddr*)&address, sizeof(address));

    struct pollfd fds[] = {
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

    char name[256];
    printf("Enter your name: ");
    fgets(name, 256, stdin);
    name[strcspn(name, "\n")] = '\0';  // remove newline char

    for(;;){
        char buffer[256];
        char message[256 * 2];
        poll(fds, 2, 50000);

        if(fds[0].revents & POLLIN){
            int bytes_read = read(0, buffer,255);
            buffer[bytes_read] = '\0';
            snprintf(message, sizeof(message), "%s: %s", name, buffer);
            send(socketfd, message, strlen(message), 0);
        }
        else if(fds[1].revents & POLLIN) {
            int bytes_received = recv(socketfd, buffer, 255, 0);
            buffer[bytes_received] = '\0';
            printf("%s\n", buffer);
        }
    }
}
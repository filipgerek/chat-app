#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

#define MAX_CLIENTS 5

int main(){
    int nfds = 1;
    int timeout = (1 * 60 * 1000);

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(9999);
    address.sin_addr.s_addr = 0;

    bind(socketfd, (struct sockaddr*)&address, sizeof(address));

    listen(socketfd, 5);
    printf("Waiting for connection...\n");

    struct pollfd fds[MAX_CLIENTS + 1] = {
            {
                 socketfd,
                 POLLIN,
                 0
            }
    };

    for(;;){
        char buffer[256];
        poll(fds, nfds, timeout);

        int current_size = nfds;
        for(int i = 0; i < current_size; ++i){
            if(fds[i].revents == 0) continue;
            if(fds[i].revents & POLLIN){
                if(fds[i].fd == socketfd){
                    int clientfd = accept(socketfd, 0, 0);
                    printf("Client connected!\n");
                    fds[nfds].fd = clientfd;
                    fds[nfds].events = POLLIN;
                    nfds++;
                }
                else {
                    int bytes_received = recv(fds[i].fd, buffer, 255, 0);
                    buffer[bytes_received] = '\0';
                    printf("%s\n", buffer);
                    for (int j = 1; j < nfds; ++j) {
                        if (fds[j].fd != fds[i].fd) {
                            send(fds[j].fd, buffer, bytes_received, 0);
                        }
                    }

                }
            }
        }
    }
}

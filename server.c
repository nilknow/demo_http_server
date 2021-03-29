#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int run();
int main() {
    run();
}

int run(){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd<0){
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
//    memset(&address.sin_zero, '\0', sizeof(address.sin_zero));
    address.sin_family=AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(8080);
    int bind_fd = bind(server_fd, (const struct sockaddr *) &address, sizeof(address));
    if (bind_fd) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, 1000)<0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    int connect_fd;
    while (1) {
        if ((connect_fd = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) sizeof(address)) < 0)) {
            perror("cannot accept socket connection");
            exit(EXIT_FAILURE);
        }

        char buffer[1024] = {0};
        int valread = read(connect_fd, buffer, 1024);
        printf("%s\n", buffer);
        if (valread < 0) {
            printf("no bytes in buffer to read");
        }
        char *hello = "hello from server";
        write(connect_fd, hello, strlen(hello));
        close(connect_fd);
    }
    return 0;
}

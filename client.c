#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    setbuf(stdout, NULL);// in case console cache the output
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("invalid IP address");
        exit(EXIT_FAILURE);
    }
    printf("%x\n", serv_addr.sin_addr.s_addr);

    if (connect(socket_fd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    char *message = "hello from client";
    send(socket_fd, message, strlen(message), 0);
    char buffer[1024]={0};
    read(socket_fd, buffer, 1024);
    printf("%s\n", buffer);
    return 0;
}
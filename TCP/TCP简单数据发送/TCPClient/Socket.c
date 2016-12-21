#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int connectsock(char* server_ip, int server_port, int type){
    int sock_fd = socket(AF_INET, type, 0);
    if(-1 == sock_fd){
        printf("create socket error\n");
        return -1;
    }

    struct sockaddr_in server_addr;
    //设置服务器地址
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    //连接服务器
    if(-1 == connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in))){
        printf("connect server error\n");
        return -1;
    }

    printf("connect server success\n");
    return sock_fd;
}

int connect_tcp(char* server_ip, int server_port){
    return connectsock(server_ip, server_port, SOCK_STREAM);
}

int connect_udp(char* server_ip, int server_port){
    return connectsock(server_ip, server_port, SOCK_DGRAM);
}


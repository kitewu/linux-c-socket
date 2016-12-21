#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define LISTEN_SIZE 20

int start_server(int port, int type){
    //建立服务器套接字
    int ss = socket(AF_INET, type, 0);
    if(ss < 0){
        printf("create socket error\n");
        return -1;
    }

    //设置服务器地址
    struct sockaddr_in server_addr;	//服务器地址结构
    bzero(&server_addr, sizeof(struct sockaddr_in)); //清零
    server_addr.sin_family = AF_INET; //协议族
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //ip地址
    server_addr.sin_port = htons(port); //端口
    //绑定地址结构到套接字描述符
    if(bind(ss, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("bind error\n");
        return -1;
    }
    //TCP
    if(SOCK_STREAM == type){
        //设置侦听
        if(listen(ss, LISTEN_SIZE) < 0){
            printf("listen error\n");
            return -1;
        }
        printf("tcp server start\n");
    }
    else
        printf("udp server start\n");
    return ss;
}

int create_tcp_server(int port){
    start_server(port, SOCK_STREAM);
}

int create_udp_server(int port){
    start_server(port, SOCK_DGRAM);
}

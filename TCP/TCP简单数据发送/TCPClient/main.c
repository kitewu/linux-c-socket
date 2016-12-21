#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>

#define SERVER "127.0.0.1"
#define PORT 8888
#define BUFF_SIZE 1024
int sock;

//从服务器读取消息
void read_data_from_server(){
    char buffer[BUFF_SIZE];
    ssize_t size;
    while(1){
        memset(buffer, 0, sizeof(buffer));
        size = read(sock, buffer, BUFF_SIZE);
        if(size > 0)
            printf("%s\n", buffer);
        else {
            printf("disconnect\n");
            close(sock);
            exit(-1);
        }
    }
}

//向服务器发送消息
void write_data_to_server(){
    char data[BUFF_SIZE];
    while(1){
        memset(data, 0, sizeof(data));
        scanf("%s", data);
        if(-1 == write(sock, data, sizeof(data)))
            printf("write error\n");
    }
}

int main(){
    sock = connect_tcp(SERVER, PORT);
    if(-1 == sock)
        return -1;

    pthread_t pid;
    pthread_create(&pid, NULL, read_data_from_server, NULL);
    write_data_to_server();
    close(sock);
    return 0;
}



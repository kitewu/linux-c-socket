//#include <stdio.h>
//#include <pthread.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>

//#define PORT 8888
//#define BUFF_LEN 1024

//int client_sock;
//void process_client();

//int main(){
//    int ss = create_tcp_server(PORT);
//    if(-1 == ss)
//        exit(-1);
//    while(1){
//        //接受客户端连接
//        socklen_t addrlen = sizeof(struct sockaddr);
//        struct sockaddr_in client_addr;	//客户端地址结构
//        client_sock = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
//        if(client_sock < 0){
//            printf("accept error\n");
//        }
//        printf("accept client %d success\n", client_sock);

//        pthread_t pid;
//        if(pthread_create(&pid, NULL, process_client, NULL) < 0){
//            printf("pthread_create error\n");
//        }
//    }
//}

////处理客户端
//void process_client(){
//    int sc = client_sock;
//    ssize_t size = 0;
//    char buffer[BUFF_LEN];
//    while(1){
//        memset(buffer, 0, sizeof(BUFF_LEN));
//        size = read(sc, buffer, BUFF_LEN);
//        if(size > 0){
//            printf("%s\n", buffer);
//            write(sc, buffer, BUFF_LEN);
//        }
//    }
//}



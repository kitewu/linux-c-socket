///*多进程实现接收多个客户端的文件*/
//#include <stdio.h>
//#include <fcntl.h>
//#include <wait.h>
//#include <stdlib.h>
//#include <signal.h>
//#include <pthread.h>
//#include <sys/stat.h>
//#include <arpa/inet.h>
//#include <sys/types.h>
//#include <sys/socket.h>

//#define PORT 8888
//#define BUFF_SIZE 1024

//typedef struct{
//    char type;
//    char data[BUFF_SIZE];
//}m_package;

//int process_client(int);
//void reaper(int);

//int main(){
//    int ss = create_tcp_server(PORT);
//    if(-1 == ss)
//        exit(-1);
//    (void) signal(SIGCHLD, reaper);
//    while(1){
//        //接受客户端连接
//        socklen_t addrlen = sizeof(struct sockaddr);
//        struct sockaddr_in client_addr;	//客户端地址结构
//        int client_sock = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
//        if(client_sock < 0){
//            printf("accept error\n");
//        }
//        printf("accept success\n");
//        int pid = fork();
//        if(pid == 0){
//            process_client(client_sock);
//        } else if(pid == -1){
//            printf("创建进程失败\n");
//        }
//    }
//}

////处理客户端程序
//int process_client(int sockid){
//    int size = 0, fd, count = 0;
//    m_package pac;
//    long total = 0, cur = 0;
//    //循环接收文件
//    while(1) {
//        memset(&pac, 0, sizeof(pac));
//        size = read(sockid, &pac, sizeof(pac));
//        if(size > 0){
//            if (pac.type == 1){
//                fd = open(pac.data, O_CREAT|O_WRONLY, 0777);
//                if(-1 == fd){
//                    printf("open file error!\n");
//                    continue;
//                }
//                count = total = cur = 0;
//            }
//            else if (pac.type == 2){
//                cur += write(fd, pac.data, strlen(pac.data));
//                if(count++ % 5000 == 0){
//                    printf("recv from client < %d > : %.01lf\%\n", sockid, cur * 100.0 / total);
//                    count = 0;
//                }
//            }
//            else if (pac.type == 3){
//                printf("recv from client < %d > : 100.0\%\n", sockid);
//                printf("recv success\n");
//                close(fd);
//            }
//            else if(pac.type == 4){//文件长度
//                total = strtol(pac.data, NULL, 10);
//                printf("%ld\n", total);
//            }
//        }else{
//            printf("client disconnected\n");
//            close(sockid);
//            break;
//        }
//    }
//    return 0;
//}

//void reaper(int sig){
//    int status;
//    while(wait3(&status, WNOHANG, (struct rusage *) 0) >= 0);
//}



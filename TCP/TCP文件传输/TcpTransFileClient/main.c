#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>

#define PORT 8888
#define BUFF_SIZE 1024

typedef struct{
    char type;
    char data[BUFF_SIZE];
}m_package;

int main(){
    //创建连接
    int sock_fd = connect_tcp("192.168.134.188", PORT);
    if(-1 == sock_fd)
        return -1;

    m_package pac;
    int fd, cur = 0, count = 0;
    long filesize = 0;
    while(1){
        //打开文件
        memset(&pac, 0, sizeof(pac));
        pac.type = 1;
        // strcpy(pac.data, "/home/SKZH/a.txt");
        scanf("%s", pac.data);
        //获取文件信息
        struct stat sfile;
        stat(pac.data, &sfile );
        filesize = sfile.st_size;
        time_t t;
        long begin = time(&t);
        cur = count = 0;

        fd = open(pac.data, O_RDONLY);
        if(-1 == fd){
            printf("file open error\n");
            continue;
        }
        //读取文件并发送
        //发送文件名
        strcpy(pac.data, strrchr(pac.data, '/') + 1);
        write(sock_fd, &pac, sizeof(pac));
        memset(&pac, 0, sizeof(pac));

        //发送文件长度
        pac.type = 4;
        sprintf(pac.data,"%ld",filesize);
        write(sock_fd, &pac, sizeof(pac));
        memset(&pac, 0, sizeof(pac));

        int read_len = 0;
        while((read_len = read(fd, pac.data, BUFF_SIZE)) > 0){
            pac.type = 2;
            write(sock_fd, &pac, sizeof(pac));
            memset(&pac, 0, sizeof(pac));
            cur += read_len;
            if(count++ % 5000 == 0){
                count = 0;
                printf("send to server : %.1lf\%\n", cur * 100.0 / filesize);
            }
        }

        //发送结束标记
        memset(&pac, 3, sizeof(pac));
        write(sock_fd, &pac, BUFF_SIZE + 1);
        close(fd);

        printf("send to server : 100.0\%\n");
        printf("file size : %d B\n", filesize);
        printf("time : %ld ms\n", time(&t) - begin);
        printf("send file success\n");
        printf("------------------------\n");
    }
    close(sock_fd);
}


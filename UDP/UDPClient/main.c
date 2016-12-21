#include <stdio.h>
#include <string.h>

#define IP "127.0.0.1"
#define PORT 8888
#define BUFF_LEN 1024

void udpclie_echo(int s){
    char buff[BUFF_LEN];
    while(1){
        bzero(buff, BUFF_LEN);
        scanf("%s", buff);
        write(s, buff, BUFF_LEN);
        bzero(buff, BUFF_LEN);
        read(s, buff, BUFF_LEN);
        printf("recved:%s\n",buff);
    }
}

int main(){
    int s = connect_udp(IP, PORT);
    if(-1 == s)
        exit(-1);
    udpclie_echo(s);
    close(s);
    return 0;
}


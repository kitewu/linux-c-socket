#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8888
#define BUFF_LEN 1024

void udpserv_echo(int ss, struct sockaddr* client){
    int n;
    char buff[BUFF_LEN];
    socklen_t len;
    while(1){
        bzero(buff, BUFF_LEN);
        len = sizeof(*client);
        n = recvfrom(ss, buff, BUFF_LEN, 0, client, &len);
        sendto(ss, buff, n, 0, client, len);
        printf("recv :%s\n", buff);
    }
}

int main(){
    int ss = create_udp_server(PORT);
    if(-1 == ss)
        exit(-1);

    //回显处理程序
    struct sockaddr_in addr_clie;
    udpserv_echo(ss, (struct sockaddr*)&addr_clie);
    close(ss);
    return 0;
}

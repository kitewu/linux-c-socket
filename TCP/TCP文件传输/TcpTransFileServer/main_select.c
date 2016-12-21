#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdarg.h>

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define PORT 8888
#define BUFF_LEN 1024

int client_sock;
int	errexit(const char *format, ...);
int echo(int fd);

int main(){
    int ss = create_tcp_server(PORT);
    if(-1 == ss)
        exit(-1);

    struct sockaddr_in fsin;
    unsigned int alen;
    int fd;
    fd_set rfds;/* read file descriptor set	*/
    fd_set afds;/* active file descriptor set	*/
    int nfds = getdtablesize();
    FD_ZERO(&afds);
    FD_SET(ss, &afds);

    while (1) {
        memcpy(&rfds, &afds, sizeof(rfds));
        if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0) < 0){
            errexit("select: %s\n", strerror(errno));
        }

        if (FD_ISSET(ss, &rfds)) {
            alen = sizeof(fsin);
            int ssock = accept(ss, (struct sockaddr *)&fsin, &alen);
            if (ssock < 0)
                errexit("accept: %s\n", strerror(errno));
            else
                printf("accept clinet %d\n", ssock);
            FD_SET(ssock, &afds);
        }
        for (fd = 0; fd < nfds; ++fd){
            if (fd != ss && FD_ISSET(fd, &rfds)){
                if (echo(fd) <= 0) {
                    (void) close(fd);
                    FD_CLR(fd, &afds);
                }
            }
        }
    }
}

int echo(int fd){
    char buf[BUFF_LEN];
    int	cc = read(fd, buf, sizeof(buf));
    if(cc > 0){
        printf("recv msg from client %d : %s\n", fd, buf);
        if(write(fd, buf, cc) < 0)
            printf("write to client %d error, close!\n", fd);
    } else if(cc == 0)
        printf("client %d disconnect\n", fd);
    else
        printf("read from client %d error, close!\n", fd);
    return cc;
}

int errexit(const char *format, ...){
    va_list	args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}



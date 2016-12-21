#include <error.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
int main()
{
    int fd = open("./read.txt", O_RDONLY | O_CREAT, 0666);
    if (-1 == fd){
        perror("open file error");
        return;
    }
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    ssize_t readlen = read(fd, buff, 1024);
    printf("%s", buff);
    printf("%d\n", readlen);
    close(fd);
    return 0;
}

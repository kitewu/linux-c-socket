#include <error.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
int main()
{
    int fd = open("./write.txt", O_WRONLY  | O_CREAT, 0666);
    if (-1 == fd){
        perror("open file error");
        return;
    }
    char* buff = "write data to file!";
    ssize_t writelen = write(fd, buff, strlen(buff));
    printf("%d\n", writelen);
    close(fd);
    return 0;
}

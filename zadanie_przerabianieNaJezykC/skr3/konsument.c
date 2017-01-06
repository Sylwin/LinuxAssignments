#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char * fifoPath = "PIPE";
    char buf[MAX_BUF];
    fd = open(fifoPath, O_RDONLY);
    dup2(3,0);
    for(int i = 0 ; i < 15;i++)
    {
        //printf("konsument\n");
        //fscanf(stdin,"%s",buf);
        read(0, buf, MAX_BUF);
        printf("Received: %s\n", buf);
    }
    close(fd);

    return 0;
}

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd;
    char * fifoPath = "PIPE";
    fd = open(fifoPath, O_WRONLY);
    for(int i = 0; i < 15;i++)
    {
        char buf[10];
        sprintf(buf,"--%d--",i);
        fprintf(stderr, buf,sizeof(buf));
        printf("producent\n");
        //write(stderr, buf,sizeof(buf));
        sleep(1);
    }
    close(fd);


    return 0;
}


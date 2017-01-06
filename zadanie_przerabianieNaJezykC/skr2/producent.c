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
    dup2(3,1);
    for(int i = 0; i < 15;i++)
    {
        char buf[10];
        printf("--%d--",i);
        //sprintf(buf,"--%d--",i);
        //fprintf(1, buf,sizeof(buf));
        //printf("producent\n");
        //write(3, buf,sizeof(buf));
        //sleep(1);
    }
    close(fd);


    return 0;
}


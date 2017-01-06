#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    char *fifoPath = "PIPE";
    mkfifo(fifoPath, 0666);
    int fd = open(fifoPath,O_RDWR);
    if(fork() > 0)
    {
        dup2(fd,2);
        char* producent[] = {"producent.o",(char*)0};
        execvp("./producent.o",producent);
    }
    if(fork() > 0)
    {
        dup2(fd,0);
        char* konsument[] = {"konsument.o",(char*)0};
        execvp("./konsument.o",konsument);
    }
    wait(NULL);
    close(fd);
    unlink(fifoPath);
    return 0;
}

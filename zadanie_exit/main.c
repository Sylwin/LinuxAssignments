#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

void killProcOnExit(int st,void * pid)
{
    kill((pid_t)pid,SIGKILL);
    printf("killing : %d\n",(int)pid);
}


int main(int argc, char * argv[])
{
    char* podwykonawca[] = {"pod.o","","","",(char*)0};
    for(int i = 0; i < 3; i++)
    {
        sleep(1);
        pid_t pid;
        if((pid = fork()) == 0)
        {
            char* arg[] = {"zasob.o",(char*)0};
            execvp("./zasob.o",arg);
        }
        else
        {
            //podwykonawca[i+1] = pid;
            int res;
            for(int i = 0; i < 3; i++)
            {
                res = waitpid(pid,NULL,WNOHANG);
            }
            if(res == 0)
            {
                on_exit(killProcOnExit,(void*)pid);
            }
        }
    }
    if(fork()==0)
    {
        if(execvp("./pod.o",podwykonawca) ==-1)
            printf("sdfasd: %d\n",errno);
    }
    return 0;
}

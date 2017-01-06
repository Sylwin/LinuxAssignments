#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
enum state {STOPPED,RUNING,EXITED,KILLED };

void childSignal(int _, siginfo_t * info,void * context)
{
    int code = info->si_code;
    if(code == CLD_KILLED)
    {
        printf("Child killed\n");
    }
    else if(code == CLD_EXITED)
    {
        printf("Child exited\n");
    }
}


int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        printf("Too few arguments...\n");
        exit(1);
    }
    struct sigaction sa;
    sa.sa_sigaction = childSignal;
    //sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    if(sigaction (SIGCHLD, &sa, NULL) == -1)
        printf("zjebalo sie \n");

    for(int i = 1u ; i < argc ;i++)
    {
        int id = 123;
        if((id = fork()) == 0)
        {
            char* signal = NULL;
            printf("arg : %s\n", argv[i]);
            float time = strtof(argv[i], &signal);
            printf("Value : %lf, rest : %d \n", time, signal);
            char killArg[20];
            char toutArg[20];
            char siblingArg[20];
            sprintf(killArg,"--kill=%s",signal);
            sprintf(toutArg,"--tout=%lf",time);
            sprintf(siblingArg,"--sibling=%d",getpid());
            char * newArgs[] =
            {
                "child.o",
                killArg,
                toutArg,
                siblingArg,
                (char *) 0
            };
            if(execvp("./child.o",newArgs)==-1)
            {
                printf("Zjebło się ;c\n");
            }
            break;
        }
        else
            printf("Jestem tatus!\n");
    }
    while(1);
    return 0;
}

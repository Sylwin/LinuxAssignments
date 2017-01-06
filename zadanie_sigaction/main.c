#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

int t;
int i;
int t1;

void sigusr1Handler(int signum)
{
    printf("Zeruje licznik\n");
    i = 0;
}

void sigusr2Handler(int signum)
{
    t = t1;
    printf("Zmieniam interwal na : %d\n",t);
}

int main(int argc, char * argv[])
{
    if(argc < 3)
    {
        printf("za malo argumentow\n");
        return 1;
    }
    t = atoi(argv[1]);
    t1 = atoi(argv[2]);
    printf("%d\n",getpid());
    struct sigaction sa;
    sa.sa_handler = sigusr1Handler;
    sa.sa_flags = 0;
    sigaction(SIGUSR1,&sa,NULL);
    sa.sa_handler = sigusr2Handler;
    sigaction(SIGUSR2,&sa,NULL);
    struct timeval sl;
    while(1)
    {
        printf("--%d ",i++);
        fflush(stdout);
        sl.tv_sec = t;
        sl.tv_usec = 0;
        while( select(0,NULL,NULL,NULL,&sl) && errno == EINTR ) {
        }
    }
    return 0;
}

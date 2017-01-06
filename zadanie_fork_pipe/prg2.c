#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>

struct sibling
{
    int bytesRead;
    bool isAlive;
    int pid;
    int pipeDescriptor[2];
};

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int opt;
    struct timespec waitTime;
    int count;
    float time;

    while ((opt = getopt(argc, argv, "t:c:")) != -1)
    {
        switch (opt)
        {
        case 't':
            time = strtof(optarg,NULL);
            waitTime.tv_sec = floor(time);
            waitTime.tv_nsec = (waitTime.tv_sec - time)*1000000000;
            break;
        case 'c':
            count = atoi(optarg);
            break;
        }
    }
    printf("PARENT !!! time : %lf, count : %d",time,count);

    struct sibling* siblings = (struct sibling*)malloc(count* sizeof(struct sibling));
    for(int i = 0; i < count;i++)
    {
        sleep(1);
        if(pipe(&siblings[i].pipeDescriptor))
        {
            perror("pipe()");
        }
        int pid;
        if((pid = fork()) > 0)
        {
            siblings[i].pid = pid;
            siblings[i].isAlive = true;
            siblings[i].bytesRead = 0;
            close(siblings[i].pipeDescriptor[1]);
        }
        else
        {
            close(siblings[i].pipeDescriptor[0]);
            char timeArg[20];
            char stringArg[20] = {"-sskjvkjxchvkj"};
            char descriptorArg[20];
            sprintf(timeArg,"-t%lf",(1.0*rand()/RAND_MAX)*3.0/4.0*time);
            sprintf(descriptorArg,"-d%d",siblings[i].pipeDescriptor[1]);
            char * newArgs[] =
            {
            "./prg1.o",
            stringArg,
            descriptorArg,
            timeArg,
            (char *) 0
            };

            if(execvp("./prg1.o",newArgs)==-1)
            {
                printf("Zjebło się ;c numer:%d\n", errno);
            }
        }
    }
    int siblingsAlive = count;

    char buffer[25];
    int size;
    while(1)
    {
        printf("pentla\n");
        nanosleep(&waitTime,NULL);
        for(int i = 0 ; i < count;i++)
        {
            if(siblings[i].isAlive)
            {
                size = read(siblings[i].pipeDescriptor[0],buffer,25);
                if(size == -1)
                {
                    perror("read()");
                }
                siblings[i].bytesRead += size;
                printf("from pid %d read %s\n",siblings[i].pid,buffer);
            }
        }
    }
}

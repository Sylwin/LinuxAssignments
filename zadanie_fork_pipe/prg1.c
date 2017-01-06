#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
    srand(time(NULL));
    int opt;
    struct timespec waitTime;
    char* string;
    int descriptor;
    float time;

    while ((opt = getopt(argc, argv, "t:s:d:")) != -1)
    {
        switch (opt)
        {
        case 't':
            time = strtof(optarg,NULL);
            waitTime.tv_sec = floor(time);
            waitTime.tv_nsec = (waitTime.tv_sec - time)*1000000000;
            break;
        case 's':
            string = (char*)malloc(strlen(optarg));
            strcpy(string,optarg);
            break;
        case 'd':
            descriptor = atoi(optarg);
            break;
        }
    }
    printf("time : %lf , string : %s , fd : %d\n",time, string, descriptor);

    while(1)
    {
        nanosleep(&waitTime,NULL);
        if(write(descriptor,string,strlen(string)) == -1)
        {
            perror("write");
            return 1;
        }
        float choice = (1.0*rand()/RAND_MAX);
        printf("choice : %lf\n",choice);
        if(choice > 0.5)
        {
            printf("child with pid : %d exited!!\n",getpid());
            return 1;
        }
    }
}

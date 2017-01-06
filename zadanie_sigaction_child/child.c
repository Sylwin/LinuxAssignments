#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int c;
    if(argc < 4)
    {
        printf("Too few arguments...\n");
        exit(1);
    }
    int signal;
    float time;
    int sibling;
    while (1)
    {
        int option_index = 0;
        static struct option long_options[] = {
        {"kill",     required_argument, 0,  'k' },
        {"tout",  required_argument,       0,  't' },
        {"sibling",  required_argument, 0,  's' },
        {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "k:t:s:",
        long_options, &option_index);
        if (c == -1)
        break;

        switch (c) {
        case 'k':
            if(!strcmp(optarg,"STOP"))
                signal = SIGSTOP;
            else if(!strcmp(optarg,"TSTP"))
                signal = SIGTSTP;
            else if(!strcmp(optarg,"TTIN"))
                signal = SIGTTIN;
            else if(!strcmp(optarg,"TTOU"))
                signal = SIGTTOU;
            printf("kill : %d\n",signal);
            break;
        case 't':
            time = strtof(optarg,NULL);
            printf("tout : %s\n",optarg);
            break;
        case 's':
            sibling = atoi(optarg);//strtol(optarg,NULL,1);
            printf("sibling : %d\n",getpid());
            break;
        }
    }
    while(1)
        pause();
}

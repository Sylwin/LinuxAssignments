#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main()
{
    int numberOfFIFOs = 1;
    struct dirent* dp;
    DIR* dir = opendir("fifos");
    while ((dp = readdir(dir)) != NULL)
    {
        if(strcmp(".",dp->d_name)&&strcmp("..",dp->d_name))
        {
            numberOfFIFOs++;
            printf("%s\n",dp->d_name);
        }
    }
    closedir(dir);
    struct pollfd* pollfds = (struct pollfd*)malloc(numberOfFIFOs*sizeof(struct pollfd));

    dir = opendir("fifos");
    int i = 0;
    while ((dp = readdir(dir)) != NULL)
    {
        if(strcmp(".",dp->d_name)&&strcmp("..",dp->d_name))
        {
            char fullName[100];
            sprintf(fullName,"fifos/%s",dp->d_name);
            int fd = open(fullName,O_RDWR);
            if(fd == -1)
            {
                printf("wrong file %s\n",fullName);
            }
            pollfds[i].fd = fd;
            pollfds[i].events = POLLIN;
            pollfds[i].revents = 0;
        }
    }
    //closedir(dir);

    //int fd = open("FIFO",O_RDWR);
    //chmod("FIFO",00666);
    int res;
    while(1)
    {
        res = poll(pollfds,numberOfFIFOs,-1);
        printf("res %d\n",res);
        for(int i = 0 ; i < numberOfFIFOs; i++)
        {
            if(pollfds[i].revents == POLLIN)
            {
                char buffer[100];
                read(pollfds[i].fd,buffer,100);
                printf("from fd : %d read : %s\n",pollfds[i].fd,buffer);
            }
            else if(pollfds[i].revents == POLLERR)
            {
                printf("from fd %d POLLERR\n",pollfds[i].fd);
            }
            else if(pollfds[i].revents == POLLNVAL)
            {
                printf("from fd %d POLLNVAL\n",pollfds[i].fd);
            }

        }
    }

    return 0;
}

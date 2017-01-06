#include <time.h>
#include <stdio.h>
int main()
{
    struct timespec time = {1,0}; 
    int i = 0;
    while(1)
    {
        printf("%d\n",i++);
        fflush(stdout);
        nanosleep(&time,NULL);
    }
    return 0;
}

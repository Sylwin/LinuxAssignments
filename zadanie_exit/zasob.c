#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int main()
{
    srand(time(NULL));
    float res = (float)random()/RAND_MAX;
    printf("res = %lf\n",res);
    if(res < 0.4)
        while(1);
    printf("Died ;/\n");
    return 0;
}

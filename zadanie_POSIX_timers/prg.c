#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char c;
    while (1)
    {
        int option_index = 0;
        static struct option long_options[] = {
        {"total", required_argument, 0, 't' },
        {"update",  required_argument, 0, 'u' },
        {0, 0, 0, 0 }
        };

        c = getopt_long(argc, argv, "t:u:",
            long_options, &option_index);
        if (c == -1)
        break;

        switch (c) {
        case 't':
            break;
        case 'u':
            break;
        }
    }

    while(optind < argc)
    {
        printf("argument : %s\n",argv[optind++]);
    }

    return 0;
}



#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("error!");
        exit(-1);
    }
    char *t = argv[1];
    int res = sleep(atoi(t));
    exit(res == 0 ? 0 : 1);
}
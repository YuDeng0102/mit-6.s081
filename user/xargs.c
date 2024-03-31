#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
    char *eargs[MAXARG];
    int argcnt = 0;
    for (int i = 1; i < argc; i++)
        eargs[argcnt++] = argv[i];

    char temchar;
    char buf[512];

    while (1)
    {
        int pos = 0, startpos = 0;
        while (1)
        {
            if (!read(0, &temchar, 1))
                exit(0);

            if (temchar != ' ' && temchar != '\n')
                buf[pos++] = temchar;
            else if (temchar == ' ')
            {
                buf[pos++] = 0;
                eargs[argcnt++] = &buf[startpos];
                startpos = pos;
            }
            else
            {
                eargs[argcnt++] = &buf[startpos];
                startpos = pos;
                break;
            }
        }
        if (fork() == 0)
        {
            exec(eargs[0], eargs);
        }
        else
            wait(0);
    }
    exit(0);
}
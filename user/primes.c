#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define SIZE_INT 4
void work(int p[2])
{
    close(p[1]);
    int x;
    if(!read(p[0], &x, SIZE_INT)){
        exit(0);
    }else printf("prime %d\n",x);
    
    int newp[2];
    pipe(newp);
    if (fork() == 0)
    {
        work(newp);
    }else
    {
        close(newp[0]);
        int num;
        while (read(p[0], &num,SIZE_INT))
        {
            if (num % x)
            {
                write(newp[1], &num,SIZE_INT);
            }
        }
        close(newp[1]);
        close(p[0]);
        wait(0);
    }
}
int main(int argc, char **argv)
{

    int p[2];
    pipe(p);
  
    if(fork()==0){
        work(p);
    }else{
        close(p[0]);
        for (int i = 2; i <= 35; i++)
        {
            write(p[1], &i,SIZE_INT);
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}
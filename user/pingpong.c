#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv)
{
   int p[2];
   pipe(p);
   int pid = fork();
   char s[10];
   if (pid == 0)
   {
      read(p[0], s, 1);
      close(p[0]);
      printf("%d: received ping\n", getpid());
      s[0] = 'c';
      write(p[1], s, 1);
      close(p[1]);
      exit(0);
   }
   else
   {
      s[0] = 'p';
      write(p[1], s, 1);
      close(p[1]);
      wait(0);
      read(p[0], s, 1);
      close(p[0]);
      printf("%d: received pong\n", getpid());
   }
   exit(0);
}
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

#define PATH_LEN 512

char*
fmtname(char *path)
{
  char *p;
  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  return p;
}
void find(char* path,char *last,char* obstr){
    char *p;
    int fd;
    struct dirent de;
    struct stat st;
    if((fd = open(path, O_RDONLY)) < 0){
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }
    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }
    switch(st.type){
  case T_DEVICE:
    break;
  case T_FILE:
    //printf("suffix:%s\n",fmtname(path));
   if(!strcmp(obstr,fmtname(path))) printf("%s\n",path);
    break;

  case T_DIR:
    // printf("strlen of path:%d\nsizeof path%d\n",strlen(path),sizeof path);
    if(strlen(path) + 1 + DIRSIZ + 1 >PATH_LEN){
      printf("ls: path too long\n");
      break;
    }
  
    *last = '/';
    last++;
    
    p=last;
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
       int i=0;
       last=p;
       while(de.name[i]) *last++=de.name[i],i++;
       *last=0;
       if(!strcmp(p,".")||!strcmp(p,"..")) continue;

      
      if(stat(path, &st) < 0){
        printf("ls: cannot stat %s\n", path);
        continue;
      }
      
      find(path,last,obstr);
    }
    break;
  }
  close(fd);
}
int
main(int argc, char *argv[])
{

  if(argc !=3){
    printf("the number of arguments should be 2!");
    exit(1);
  }
  char buf[PATH_LEN];
  strcpy(buf,argv[1]);

  find(buf,buf+strlen(argv[1]),argv[2]);
  exit(0);
}

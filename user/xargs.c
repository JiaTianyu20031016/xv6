#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"


int readline(char* buf){
    int i = 0;
    while(read(0, buf+i, 1) > 0){
        if(buf[i] == '\n'){
            buf[i+1] = 0;
            return 0;
        }
        i++;
    }
    return -1;
}

void split(char* line, char** arg){
    int s = 0, e = 0, count = 0;
    int flag =  1;
    while(flag){
        while(line[e]!=' ' && line[e]!='\n')
            e++;
        if(line[e] == '\n')
            flag = 0;
        line[e] = 0;
        arg[count] = (char*)malloc(e - s + 1);
        strcpy(arg[count], line+s);
        e++;
        s = e;
        count++;
    }
    arg[count] = 0;
}

int
main(int argc, char *argv[])
{
  char* arg[MAXARG + 1];
  for(int i = 1;i<argc;i++){
    arg[i-1] = (char*)malloc(strlen(argv[i]));
    strcpy(arg[i-1], argv[i]);
  }

  char buf[1024];
  while(readline(buf) == 0){
    split(buf, arg+argc-1);
    if(fork() == 0){
        exec(arg[0], arg);
        exit(0);
    }
    else
        wait(0);
  }
  exit(0);
}

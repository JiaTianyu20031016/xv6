#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int p1[2], p2[2];
int main(int argc, char* argv[]){
    if(pipe(p1) < 0 || pipe(p2) < 0){
        printf("failed to create pipe\n");
        exit(1);
    }
    int pid = fork();
    if(pid == 0){
        char c[1] = "x";
        pid = getpid();
        close(p2[1]);
        close(p1[0]);
        int n = read(p2[0], c, 1);
        if(n > 0)
            printf("%d: received ping\n", pid);
        write(p1[1], c, 1);
        exit(0);
    }
    else{
        pid = getpid();
        char c[1] = "x";
        close(p2[0]);
        close(p1[1]);
        write(p2[1], c, 1);
        int n = read(p1[0], c, 1);
        if(n > 0)
            printf("%d: received pong\n", pid);
        exit(0);
    }
}
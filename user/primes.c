#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int p1[2];
int main(int argc, char* argv[]){
    pipe(p1);
    for(int x = 2;x <= 35;x++)
        write(p1[1], (char*)&x, sizeof(x));
    while(1){
        int pid = fork();
        if(pid == 0){
            int x, y;
            close(p1[1]);
            int n = read(p1[0], (char*)&x, sizeof(x));
            if(n <= 0)
                exit(n);
            printf("prime %d\n", x);
            int tmp[2];
            pipe(tmp);
            while(read(p1[0], (char*)&y, sizeof(x)) > 0)
                if(y % x != 0)
                    write(tmp[1], (char*)&y, sizeof(x));
            close(p1[0]);
            p1[0] = tmp[0];
            p1[1] = tmp[1];
        }
        else{
            close(p1[0]);
            close(p1[1]);
            while(wait(0) != -1);
            exit(0);
        }
    }
}
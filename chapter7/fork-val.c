#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    int i = 100;
    pid = fork();//fork()は、呼びだされた後に複数のプロセスにわかれる

    if(pid==0){
        /*子プロセスはprintf()を実行してexit()によって終了*/
        printf("child process : %d\n", getpid());
        i += 500;
    }else{

        printf("parent process : childpid=%d, mypid=%d\n",pid,getpid());

        i += 1024;
        
    }

    printf("i=%d\n", i);

    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    pid = fork();//fork()は、呼びだされた後に複数のプロセスにわかれる

    if(pid==0){
        /*子プロセスはprintf()を実行してexit()によって終了*/
        printf("child process : %d\n", getpid());
        exit(0);
    }else{
        int status;
        pid_t waitpid;

        /*
        親プロセスはprintf()を実行後に子プロセスの終了をwait()によって待っている
        親プロセスがwait()を行って子プロセスの終了を完了させなければ、子プロセスは「ゾンビプロセス」としてカーネル内に残る
        */

        printf("parent process : childpid=%d, mypid=%d\n",pid,getpid());
        waitpid = wait(&status);

        printf("waitpid : %d\n", waitpid);
    }
    return 0;
}
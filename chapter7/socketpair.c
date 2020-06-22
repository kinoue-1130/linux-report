#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int sv[2];
    pid_t pid;
    char buf[128];

    memset(buf,0,sizeof(buf));

    /*ソケットペアを作成*/
    if(socketpair(AF_UNIX,SOCK_STREAM,0,sv) != 0){
        perror("pipe");
        return 1;
    }

    /*プロセスを増やしている*/
    pid = fork();
    if(pid < 0){
        perror("fork");
        return 1;
    }

    if(pid == 0){
        /*
        子プロセス側はsv[1]を閉じてsv[0]を利用
        親プロセスからのデータを受信
        */
        close(sv[1]);
        read(sv[0],buf,sizeof(buf));
        printf("child process : data from parent process [%s]\n", buf);
        exit(0);
    }else{
        /*
        親プロセス側はsv[0]を閉じてsv[1]を利用
        sv[1]に対してデータを書きこむ
        データを書き込んだ後に、子プロセスの終了をwait()している
        */

        int status;
        close(sv[0]);

        write(sv[1],"HOGE",4);

        printf("parent process : child process id %d\n", pid);

        wait(&status);
    }

    return 0;
}
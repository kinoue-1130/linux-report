#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
    int p[2];
    pid_t pid;
    char buf[128];

    memset(buf,0,sizeof(buf));

    if(pipe(p) != 0){
        perror("pipe");
        return 1;
    }

    /*fork()後に親プロセスから子プロセスへパイプを通じてデータが送信される*/
    pid = fork();
    if(pid < 0){
        perror("fork");
        return 1;
    }

    if(pid == 0){
        /*
        子プロセス側は、書き出し側ファイルディスクリプタであるp[1]を閉じて
        p[0]からのデータ受信をread()で待つ
        */
        close(p[1]);
        read(p[0],buf,sizeof(buf));
        printf("child process : data from parent process [%s]\n", buf);

    }else{
        /*
        親プロセス側は、読み込み側ファイルディスクリプタであるp[0]を閉じて
        p[1]へデータを書き込む
        */

        close(p[0]);

        write(p[1],"HOGE",4);

        printf("parent process : child process id %d\n", pid);

    }

    return 0;
}
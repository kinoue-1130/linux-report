#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
    int shm;
    char *ptr;

    /*IPC_CREATなので新しいセグメント生成*/
    shm = shmget(IPC_PRIVATE,128,IPC_CREAT | 0600);

    if(shm < 0){
        perror("shmget");
        return 1;
    }

    /*shmget()で生成した共有メモリセグメント識別子を使用してshmat()を行い、
    共有メモリをプロセスのアドレス空間にアタッチ*/
    ptr = shmat(shm,NULL,0);
    if((int)ptr == -1){
        perror("shmat");
        return 1;
    }
    /*アタッチされた共有メモリに対して、strcpy()関数で文字列を書き込む*/
    strcpy(ptr,"HOGE");

    shmdt(ptr);
    

    return 0;
}
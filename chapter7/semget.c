#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NSEMS 16

int main(){
    int semid;
    unsigned short semun_array[NSEMS];
    int i;

    /*
    segmet()をIPC_PRIVATEで作成したあとに初期化
    0600はアクセス許可を８進数で示したもので、ownerに対しての読み書き権限を許可している
    */
    semid = semget(IPC_PRIVATE,NSEMS,0600);
    if(semid<0){
        perror("semget");
        return 1;
    }


    /*ここでは、セマフォに設定する初期値を１とすることで、このセマフォを待てるプロセス数を一つにできるようにしている*/
    for(i=0;i<NSEMS;i++){
        semun_array[i] = 1;
    }

    /*semctl()をSETALLで利用することによって、セマフォの初期化が行われる*/
    if(semctl(semid,NSEMS,SETALL,&semun_array) != 0){
        perror("semctl");
        return 1;
    }

    /*セフォマ識別子を表示して終了*/
    printf("%d\n",semid);
    return 0;
}
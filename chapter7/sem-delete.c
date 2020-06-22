#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NSEMS 16

int main(int argc,char *argv[]){
    int semid;
    int i;
    unsigned short semun_array[NSEMS];

    if(argc != 2){
        fprintf(stderr,"Usage : %s shmid\n",argv[0]);
        return 1;
    }

    semid = atoi(argv[1]);

    for(i=0;i<NSEMS;i++){
        semun_array[i] = 1;
    }

    if(semctl(semid,NSEMS,IPC_RMID,&semun_array) != 0){
        perror("semctl");
        return 1;
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NSEMS 16

int main(int argc,char *argv[]){
    int semid;
    struct sembuf sb;

    if(argc != 2){
        fprintf(stderr,"Usage * %s semid\n",argv[0]);
        return 1;
    }

    semid = atoi(argv[1]);

    sb.sem_num = 0;//0なので、セマフォセットの最初のひとつだけを利用している
    sb.sem_op = -1;//セマフォから１引いて値が０以上であればsemop()はすぐに返る
    sb.sem_flg = SEM_UNDO;//SEM_UNDOが指定されることで、プロセスが終了するとセマフォへの減算が取り消される

    printf("before semop()\n");

    if(semop(semid,&sb,1) != 0){
        perror("semop");
        return 1;
    }
    printf("after semop()\n");
    printf("press enter to exit\n");
    getchar();
    return 0;
}
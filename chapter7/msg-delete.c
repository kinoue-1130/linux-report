#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc,char *argv[]){
    int msgid;
    struct msqid_ds ms;

    if(argc != 2){
        fprintf(stderr,"Usage : %s msgid\n",argv[0]);
        return 1;
    }

    msgid = atoi(argv[1]);

    if(msgctl(msgid,IPC_RMID,&ms) != 0){
        perror("msgctl");
        return 1;
    }

    return 0;
}